#include <IWatchdog.h>

constexpr int BUFFER = 32;
int DEBUG = 0;
int dial = 50;
int zeros = 0;

void setup() {
  IWatchdog.begin(10000000); // 10s timeout
  Serial.begin(115200);
  Serial.setTimeout(100);
  while(!Serial);
  if (DEBUG) Serial.println("Advent of Code Day 1");
}

void loop() {
  IWatchdog.reload();
  if(Serial.available()) {
    char rot[BUFFER];
    int s = 0;
    int len = Serial.readBytesUntil('\n', rot, BUFFER - 1);
    rot[len] = '\0';
    
    switch (rot[0]) {
      case 's':
      case 'S':
        if (DEBUG) Serial.println("Reset.");
          Serial.println("READY");
        dial = 50;
        zeros = 0;
        break;
      case 'l':
      case 'L':
        s = -1;
        break;
      case 'r':
      case 'R':
        s = 1;
        break;
      case 'v':
      case 'V':
        DEBUG = !DEBUG;
        if (DEBUG) Serial.println("Debug on.");
        break;
      case 'z':
      case 'Z':
        Serial.print("Zero count is ");
        Serial.println(zeros);
        break;
      case 'd':
      case 'D':
        Serial.print("Dial position is ");
        Serial.println(dial);
        break;
      default:
        if (DEBUG) Serial.println("Durp!");
    }
    
    dial = ((dial + s * atoi(&rot[1])) % 100 + 100) % 100;
    if (dial == 0) zeros++;
    
    if (DEBUG) {
      Serial.print("Dial at ");
      Serial.println(dial);
      Serial.print("Zeros: ");
      Serial.println(zeros);
    }
    Serial.println("K");
  }
}