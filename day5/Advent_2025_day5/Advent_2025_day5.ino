#include "aoc_utils.hpp"

constexpr int BUFFER_LEN = 32;
constexpr int MAX_RANGES = 185;

uint64_t N[MAX_RANGES];
uint64_t M[MAX_RANGES];

uint32_t password = 0;
uint32_t i = 0;

enum State {WAITING, RANGE, CHECK, DONE};

enum State FSM;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
  Serial.println("Advent of Code 2025 Day 5");
  Serial.println("READY");
  i = 0;
  FSM = RANGE;
}

void loop() {
  char readBuffer[BUFFER_LEN];
  int j;
  bool overlap = false;
  int len;
  uint64_t n, m;
  if(Serial.available()) {
    char first = Serial.peek();
    switch (first) {
      case 'R':
        FSM = RANGE;
        Serial.println("RANGE");
        Serial.read();
        password = 0;
        i = 0;
        break;
      case 'C':
      //case '\n':
        FSM = CHECK;
        Serial.read();
        Serial.println("CHECK");
        break;
      case 'D':
        FSM = DONE;
        Serial.read();
        Serial.print("DONE");
        Serial.println(password);
        break; 
      default:

    switch (FSM) {
      case RANGE:

    len = Serial.readBytesUntil('-', readBuffer, BUFFER_LEN-1);
    readBuffer[len] = '\0';
    n = stringToUint64(readBuffer);
    len = Serial.readBytesUntil('\n', readBuffer, BUFFER_LEN-1);
    readBuffer[len] = '\0';
    m = stringToUint64(readBuffer);
    overlap =false;
    for(j = 0; j < i; j++) {
      if(n > N[j] && m < M[j]) {
        overlap = true;
      }else if (n < N[j] && m > M[j]) {
        N[j] = n;
        M[j] = m;
        overlap = true;
      }else{
      if(n < N[j] && m > N[j]) {
        N[j] = n;
        overlap = true;
      }
      if(m > M[j] && n < M[j]) {
        M[j] = m;
        overlap = true;
      }
      }
    }
    if (overlap == false) {
      N[i] = n;
      M[i] = m;
      i++;
    }
    Serial.println(i);
    break;
    case CHECK:
    uint32_t count = 0;
    for(j = 0; j < i; j++) {
      count += 1 + M[j] - N[j];
    }
    Serial.print("Ingredients Count: ");
    Serial.println(count);
    len = Serial.readBytesUntil('\n', readBuffer, BUFFER_LEN - 1);
    readBuffer[len] = '\0';
    bool fresh = false;
    uint64_t t = stringToUint64(readBuffer);
    for (j = 0; j < i; j++) {
      if (N[j] <= t && t <= M[j]) {
        password++;
        Serial.println("FRESH");
        fresh = true;
        break;
      }
    }
    if (fresh == false) {
      Serial.println("SPOILED");
    }
      break;
    }
            break;
    }
  }
 // Serial.println(".");
}