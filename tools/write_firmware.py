import os
Import("env")


def append_version_to_firmware(source, target, env):
    firmware_path = str(target[0])
    version_file = os.path.join(env['PROJECT_DIR'], 'configuration.bin')
    with open(firmware_path, 'ab') as f_fw, open(version_file, 'rb') as f_ver:
        f_fw.write(f_ver.read())
    print("Appended configuration.bin to firmware")


env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", append_version_to_firmware)
