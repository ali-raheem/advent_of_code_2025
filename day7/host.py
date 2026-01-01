#!/usr/bin/env python3
from sys import argv
import serial
import time

def main():
    if len(argv) != 3:
        print("Usage: python3 host.py <input_file> <serial_port>")
        print("Example: python3 host.py input /dev/ttyACM0")
        return
    
    input_file = argv[1]
    serial_port = argv[2]
    
    with open(input_file) as f:
        lines = f.readlines()
    
    print(f"Loaded {len(lines)} lines from {input_file}")
    print("Connecting to Arduino...")
    
    ser = serial.Serial(serial_port, 115200, timeout=10)
    
    while True:
        line = ser.readline().decode('utf-8').strip()
        print(f"Arduino: {line}")
        if "READY" in line:
            break
    
    for i, line in enumerate(lines):
        ser.write(f"{line.strip()}\n".encode())
        print(f"Sent line {i}: {line}")

        ack = ""
        while "ACK" not in ack:
            ack = ser.readline().decode('utf-8').strip()
            print(f"  <- {ack}")

        
    ser.write(b"DONE,")
    print("\nAll data sent. Waiting for result...")
    
    while True:
        response = ser.readline().decode('utf-8').strip()
        if response:
            print(f"Arduino: {response}")
            if "RESULT" in response or "DONE" in response:
                break

    print("Releasing serial port")
    ser.close()

if __name__ == "__main__":
    main()
