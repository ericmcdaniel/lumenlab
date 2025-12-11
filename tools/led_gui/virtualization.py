import moderngl_window as mglw
import numpy as np
import serial
import pyglet
import threading
import time
import logging


class LEDVisualizer(mglw.WindowConfig):
    title = "LumenLab LED Visualizer"
    logging.basicConfig(format='%(asctime)s - %(filename)s:%(lineno)d - %(levelname)s - %(message)s', level=logging.INFO)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.FRAME_SIZE = self.num_leds * 3
        self.SYNC_BYTES = b'\xAA\x55'

        raw_positions = self.compute_led_positions()
        self.positions = self.normalize_positions(raw_positions)

        self.led_colors = np.ones((self.num_leds, 3), dtype='f4')

        quad_vertices = np.array([
            -0.5, -0.5, 0.5, -0.5,
            -0.5,  0.5, 0.5,  0.5
        ], dtype='f4')

        # Indices for two triangles
        indices = np.array([0, 1, 2, 1, 3, 2], dtype='i4')

        self.prog = self.ctx.program(
            vertex_shader='''
        #version 330
        in vec2 in_quad;      // quad vertex offset (-0.5 to 0.5)
        in vec2 in_pos;       // LED center position
        in vec3 in_color;     // LED color

        uniform vec2 pixel_size;  // size of 1 pixel in normalized coords

        out vec3 v_color;

        void main() {
          // Scale quad to 10x10 pixels
          vec2 offset = in_quad * pixel_size * 10.0;

          gl_Position = vec4(in_pos + offset, 0.0, 1.0);
          v_color = in_color;
        }
      ''',
            fragment_shader='''
        #version 330
        in vec3 v_color;
        out vec4 f_color;
        void main() {
          f_color = vec4(v_color, 1.0);
        }
      ''',
        )

        self.vbo_quad = self.ctx.buffer(quad_vertices.tobytes())
        self.ibo = self.ctx.buffer(indices.tobytes())
        self.vbo_positions = self.ctx.buffer(reserve=self.num_leds * 2 * 4)
        self.vbo_colors = self.ctx.buffer(reserve=self.num_leds * 3 * 4)

        self.vao = self.ctx.vertex_array(
            self.prog,
            [
                (self.vbo_quad, '2f', 'in_quad'),
                (self.vbo_positions, '2f/i', 'in_pos'),
                (self.vbo_colors, '3f/i', 'in_color'),
            ],
            self.ibo
        )

        self.pixel_size = (
            2.0 / self.window_size[0],
            2.0 / self.window_size[1],
        )
        self.led_lock = threading.Lock()
        self.serial_thread = threading.Thread(target=self.read_serial, daemon=True)
        self.serial_thread.start()

        self.title = pyglet.text.Label(
            "LumenLab",
            font_name='Arial',
            font_size=36,
            x=self.window_size[0] // 2,
            y=self.window_size[1] // 2 + 30,
            anchor_x='center',
            anchor_y='center',
            color=(190, 190, 190, 190),
            width=300
        )
        self.description = pyglet.text.Label(
            "LED Debug Virtualizer",
            font_name='Arial',
            font_size=24,
            x=self.window_size[0] // 2,
            y=self.window_size[1] // 2 - 10,
            anchor_x='center',
            anchor_y='center',
            color=(160, 160, 160, 160),
            width=300
        )

    def compute_led_positions(self):
        led_radius = 11
        led_margin = 2
        step = led_radius + led_margin

        positions = []
        x, y = 50, 10

        segments = [
            (0, 112, step, 0),
            (113, 167, 0, step),
            (168, 280, -step, 0),
            (281, self.num_leds, 0, -step),
        ]

        corner_offsets = {
            0:   (4 * step, 4 * step),
            113: (4 * step, 4 * step),
            168: (-4 * step, 4 * step),
            281: (-4 * step, -4 * step),
        }

        for index in range(self.num_leds):
            if index in corner_offsets:
                dx, dy = corner_offsets[index]
                x += dx
                y += dy
            else:
                for start, end, dx, dy in segments:
                    if start < index <= end:
                        x += dx
                        y += dy
                        break

            positions.append((x, y))

        return positions

    def normalize_positions(self, raw_positions):
        norm_positions = []
        width, height = self.window_size
        for x, y in raw_positions:
            norm_x = (x / width) * 2.0 - 1.0
            norm_y = 1.0 - (y / height) * 2.0
            norm_positions.append((norm_x, norm_y))
        return np.array(norm_positions, dtype='f4')

    def read_serial(self):
        def process_buffer():
            """Extract complete frames from buffer and update LED colors."""
            nonlocal buffer
            while True:
                idx = buffer.find(self.SYNC_BYTES)
                if idx == -1:
                    break  # no sync bytes found yet
                if len(buffer) < idx + 2 + self.FRAME_SIZE:
                    break  # incomplete frame
                start = idx + 2
                frame = buffer[start:start + self.FRAME_SIZE]
                buffer = buffer[start + self.FRAME_SIZE:]
                with self.led_lock:
                    colors = np.frombuffer(frame, dtype=np.uint8).reshape(-1, 3) / 255.0
                    self.led_colors[:] = colors

        buffer = bytearray()
        while True:
            try:
                with serial.Serial(self.port, self.baud_rate, timeout=0) as ser:
                    logging.info("Serial connected on COM3.")
                    while True:
                        chunk = ser.read(1024)
                        if chunk:
                            buffer.extend(chunk)
                            process_buffer()
            except serial.SerialException as e:
                logging.warning(f"Serial error: {e}")
                time.sleep(1)
            except Exception as e:
                logging.warning(f"Unexpected error: {e}")
                time.sleep(1)

    def on_render(self, time, frametime):
        self.ctx.clear(0.1, 0.1, 0.1)
        with self.led_lock:
            self.vbo_positions.write(self.positions.tobytes())
            self.vbo_colors.write(self.led_colors.tobytes())
        self.prog['pixel_size'].value = self.pixel_size
        self.vao.render(instances=self.num_leds)
        self.title.draw()
        self.description.draw()


def start_led_virtualization(window_size, num_leds, port, baud_rate):
    LEDVisualizer.window_size = window_size
    LEDVisualizer.num_leds = num_leds
    LEDVisualizer.port = port
    LEDVisualizer.baud_rate = baud_rate
    mglw.run_window_config(LEDVisualizer)


if __name__ == '__main__':
    logging.info("Starting the LumenLab Virtualizer at 1680x945 with 300 LEDs. Connected through COM3 with a baud rate of 921600.")
    start_led_virtualization(window_size=(1680, 945), num_leds=300, port="COM3", baud_rate=921600)
