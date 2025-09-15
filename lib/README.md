# Third-Party Libraries

All third-party libraries used by LumenLab are contained here instead of the .pio directory. This is mostly so that PlatformIO does not force a new build after any small change to the project structure invalidates the libdep cache.

Additionally, the FastLED lib has a non-fatal warning that can only be removed by slight modification of the source, which has been done here.