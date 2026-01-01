# Advent of Code 2025

Goal is to complete [aoc](https://adventofcode.com/2025) running on a STM32 (specfically a STM32F103C6 with STM32duino bootloader).

32KB flash (about 4KB used by bootloader I think) and 10KB RAM.

`host.py` generally needed to send the input over the serial port to the microcontorller, sometimes making small changes to the input for convenience. But since the input might not all fit in the small MCU RAM sometimes the host script acts as a memory slave for the mcu.

`aoc_utils.h` or similar are some small helper functions I wrote including some functional programming helpers.
