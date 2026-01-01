# Day 1

The code runs on a arduino (STM32F103 in my case). To stop the Serial buffer being overrun we have the arduino send a 'K' once each line is processed.
The `host.py` waits for the arduino to be ready (sends 'READY') which we add `S` to start of the input vector and `Z` to end of input vector to get the number of zeros.

I run it with `time python3 host.py day1input /dev/ttyACM0`.
