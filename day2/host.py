#!/usr/bin/env python3
import serial
import sys
import time

def send(port, filename):
    ser = serial.Serial(port, 115200, timeout=30)

    time.sleep(2)
    ser.flushInput()

    ser.write(b'R')
    time.sleep(0.1)
    response = ser.readline().decode('utf-8').strip()
    if response == "RESET":
        print("Arduino reset successfully")

    password = 0

    with open(filename, 'r') as f:
        lines = f.read().split(",")
        lines = [line.strip() for line in lines if line.strip()]
        total = len(lines)

        for i, line in enumerate(lines, 1):
            ser.write((line + ",").encode())
            ser.flush()
            print(f"Sent [{i}/{total}]: {line}")

            while True:
                response = ser.readline().decode('utf-8').strip()
                if response:
                    if response.startswith('M:'):

                        match = int(response[2:])
                        password += match
                        print(f"  Match: {match}, Running total: {password}")
                    elif response == "DONE":
                        print(f"  Range complete. Total: {password}")
                        break
                    else:
                        print(f"  {response}")
                else:
                    print("  Timeout!")
                    break

    print(f"\nFinal answer: {password}")
    print("Releasing serial")
    ser.close()

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input_file> <port>")
        sys.exit(1)

    send(sys.argv[2], sys.argv[1])
