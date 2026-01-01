#!/usr/bin/env python3
from functools import reduce
from operator import add, sub, mul, floordiv
from sys import argv
import serial
import time

input_data = open(argv[1]).readlines()
*data, ops = [line.split() for line in input_data]

# sum([reduce(lambda x, y: eval(f"{x}{op}{y}"), (int(row[i]) for row in data))
#     for i, op in enumerate(ops)])
# Just kidding

OPERATIONS = {'+': add, '-': sub, '*': mul, '/': floordiv}

cols = [
    reduce(OPERATIONS[op], [int(row[i]) for row in data])
    for i, op in enumerate(ops)
]

password = sum(cols)

def get(row, col):
    if row == len(data):
        value = ops[col]
    else:
        value = data[row][col]
    
    print(f"  -> Sending [{row},{col}] = {value}")
    return f"{value},"

def info():
    return f"({len(data)},{len(data[0])})"

print(f"The password is {password}.")
print("Connecting to arduino...")

ser = serial.Serial(argv[2], 115200, timeout=10)
time.sleep(2)

while True:
    line = ser.readline().decode('utf-8').strip()
    print(f"Arduino: {line}")
    if "READY" in line:
        break

ser.write(b"GO,")
print("Handshake complete. Processing...")

while True:
    try:
        cmd = ser.readline().decode('utf-8').strip()
        
        if not cmd:
            continue
            
        print(f"Got: {cmd}")
        
        if cmd.startswith("INFO"):
            response = info()
            print(f"Sending: {response}")
            ser.write(response.encode())
        
        elif cmd.startswith("GET"):
            coords = cmd[4:-1]
            x, y = map(int, coords.split(','))
            response = get(x, y)
            ser.write(response.encode())
        
        elif cmd.startswith("CHECK"):
            params = cmd[6:-1]
            col, checksum = map(int, params.split(','))
            
            if cols[col] == checksum:
                ser.write("OK,".encode())
                print(f"✓ Column {col}={checksum}")
            else:
                ser.write("BAD,".encode())
                print(f"✗ Column {col}={checksum} (expected {cols[col]})")
        
        elif cmd.startswith("DONE"):
            res = int(cmd[5:-1])
            result = "✓ CORRECT" if res == password else "✗ WRONG"
            print(f"\nFinal: {res} == {password} ? {result}")
            break
            
    except KeyboardInterrupt:
        print("\nExiting...")
        break
    except Exception as e:
        print(f"Error: {e}")
        break

ser.close()
print("Done.")
