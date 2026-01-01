#include "aoc_utils.hpp"

constexpr int BUFFER_LEN = 32;
constexpr int MAX_DATA = 10;
char readBuffer[BUFFER_LEN];
char outBuffer[32];
int len;
uint64_t N[MAX_DATA];

uint64_t password = 0;

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(2000);
    
    while (!Serial) {
        delay(10);
    }
    
    delay(100);
    
    Serial.println("Advent of Code 2025 Day 6");
    Serial.println("READY");
    
    while (!Serial.available()) {
        delay(10);
    }
    
    while (Serial.available()) {
        Serial.read();
    }
}

int readLine() {
    unsigned long startTime = millis();
    while (!Serial.available()) {
        if (millis() - startTime > 5000) {
            return 0;
        }
        delay(10);
    }
    len = Serial.readBytesUntil(',', readBuffer, BUFFER_LEN - 1);
    readBuffer[len] = '\0';
    return len;
}

int get(int row, int col) {
    Serial.print("GET(");
    Serial.print(row);
    Serial.print(",");
    Serial.print(col);
    Serial.println(")");
    len = readLine();
    return len;
}

void loop() {
    int rows, cols;
    
    Serial.println("INFO");
    
    unsigned long startTime = millis();
    while (!Serial.available()) {
        if (millis() - startTime > 5000) {
            Serial.println("ERROR: Timeout waiting for INFO response");
            while (true) delay(1000);
        }
        delay(10);
    }
    
    char c = Serial.read();
    
    len = Serial.readBytesUntil(',', readBuffer, BUFFER_LEN - 1);
    readBuffer[len] = '\0';
    rows = atoi(readBuffer);
    
    len = Serial.readBytesUntil(')', readBuffer, BUFFER_LEN - 1);
    readBuffer[len] = '\0';
    cols = atoi(readBuffer);
    
    Serial.print("RECEIVED(");
    Serial.print(rows);
    Serial.print(",");
    Serial.print(cols);
    Serial.println(")");
    
    password = 0;
    
    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            get(row, col);
            N[row] = stringToUint64(readBuffer);
        }
        
        get(rows, col);
        char opc = readBuffer[0];
        
        uint64_t (*op)(uint64_t, uint64_t);
        switch (opc) {
            case '+':
                op = add;
                break;
            case '-':
                op = sub;
                break;
            case '*':
                op = mul;
                break;
            case '/':
                op = div;
                break;
            default:
                op = add;
                break;
        }
        
        uint64_t res = reduce(op, N, rows);
        
        Serial.print("CHECK(");
        Serial.print(col);
        Serial.print(",");
        uint64ToString(res, outBuffer);
        Serial.print(outBuffer);
        Serial.println(")");
        
        len = readLine();
        
        password += res;
    }
    
    Serial.print("DONE(");
    uint64ToString(password, outBuffer);
    Serial.print(outBuffer);
    Serial.println(")");
    
    delay(1000);
    
    while (true) {
        delay(1000);
    }
}