#include "aoc_utils.hpp"
constexpr int BUFFER_LEN = 150;
alignas(uint32_t) char buffer[BUFFER_LEN];
alignas(uint32_t) char buffer2[BUFFER_LEN];
int password = 0;

char * nextLine(int lineCount) {
    if(lineCount % 2 == 0) {
        return buffer;
    }
    return buffer2;
}

char * lastLine(int lineCount) {
    return nextLine(lineCount + 1);
}

int len;

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(2000);
    
    while (!Serial) {
        delay(10);
    }
    delay(100);
    memset(buffer, '.', BUFFER_LEN);
    memset(buffer2, '.', BUFFER_LEN);
    Serial.println("Advent of Code Day 7");
    Serial.println(__cplusplus); // was 201703 whoop!
    Serial.println("READY");
    
}

int readLine(char *readBuffer) {
    while(!Serial.available());
    len = Serial.readBytesUntil('\n', readBuffer, BUFFER_LEN - 1);
    readBuffer[len] = '\0';
    return len;
}

void loop() {
    int lineCount = 0;
    
    while (true) {
        len = readLine(nextLine(lineCount));
        if (len == 0) {
            continue;
        }
        
        // D = DONE end of input
        if (nextLine(lineCount)[0] == 'D') {
            break;
        }
        
        for(int i = 0; i < len; i++) {
            switch (nextLine(lineCount)[i]) {
                case 'S':
                    nextLine(lineCount)[i] = '|';
                    break;
                case '.':
                    if (lastLine(lineCount != '^'))
                        nextLine(lineCount)[i] = lastLine(lineCount)[i];
                    break;
                case '^':
                    if (lastLine(lineCount)[i] == '|') {
                        password++; // hit a splitter
                        nextLine(lineCount)[i - 1] = '|';
                        nextLine(lineCount)[i + 1] = '|';
                        i += 1; // skip next byte.
                    };
                    break;

            }
            // if (nextLine(lineCount)[i] == 'S') {
            //     nextLine(lineCount)[i] == '|';
            // }else if(nextLine(lineCount)[i] == '.' && lastLine(lineCount)[i]!='^') {
            //     nextLine(lineCount)[i] = lastLine(lineCount)[i];
            // }else if (nextLine(lineCount)[i] == '^' && lastLine(lineCount)[i] == '|') {
            //     password++; // beam hit a splitter so increment.
            //     nextLine(lineCount)[i - 1] = '|';
            //     nextLine(lineCount)[i + 1] = '|';
            //     }
            }

        Serial.print("ACK ");
        Serial.println(nextLine(lineCount));
        lineCount++;
    }
    
    Serial.print("RESULT(");
    Serial.print(password);
    Serial.println(")");
    
    // halt
    while (true) {
        delay(1000);
    }
}