#!/usr/bin/env python3
import serial
import sys
import time

def send_with_handshake(port, filename):
    ser = serial.Serial(port, 115200, timeout=2)
    ser.write("S\n".encode())
    while True:
        line = ser.readline().decode('utf-8').strip()
        if line == "READY":
            print("STM32 ready!")
            break
        if not line:
            print("Timeout waiting for READY")
            return

    with open(filename, 'r') as f:
        lines = f.readlines()
        total = len(lines)

        for i, line in enumerate(lines, 1):
            ser.write(line.encode())
            print(f"Sent [{i}/{total}]: {line.strip()}")

            while True:
                response = ser.readline().decode('utf-8').strip()
                if response == 'K':
                    break
                elif response:
                    print(f"Response: {response}")
                else:
                    print("Timeout waiting for K!")
                    break

    print("\nAll commands sent!\nReleasing serial")

    ser.close()

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input_file> <port>")
        sys.exit(1)
    send(sys.argv[2], sys.argv[1])
