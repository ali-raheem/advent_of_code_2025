constexpr int BUFFER_LEN = 150;
char lineA[BUFFER_LEN];
char lineB[BUFFER_LEN];
char lineC[BUFFER_LEN];
uint32_t password = 0;
int len = 0;
bool isFirstRead = true;

inline bool isRoll(char s) {
  return s == '@';
}

void clearLine(char *line) {
  memset(line, '.', BUFFER_LEN);
  line[BUFFER_LEN - 1] = '\0';
}

int readLine(char *line) {
  line[0] = '.';
  int len = Serial.readBytesUntil('\n', line + 1, BUFFER_LEN - 3);
  line[len + 1] = '.';
  line[len + 2] = '\0';
  return len + 2;
}

void processCurrentLine() {
  for(int i = 1; i < len - 1; i++) {
    if(lineB[i] == '@') {
      int count = isRoll(lineA[i-1]) + isRoll(lineA[i]) + isRoll(lineA[i+1])
                + isRoll(lineB[i-1])                     + isRoll(lineB[i+1])
                + isRoll(lineC[i-1]) + isRoll(lineC[i]) + isRoll(lineC[i+1]);
      if (count < 4) {
        password++;
      }
    }
  }
}

void shiftBuffers() {
  memcpy(lineA, lineB, BUFFER_LEN);
  memcpy(lineB, lineC, BUFFER_LEN);
}

void resetState() {
  clearLine(lineA);
  clearLine(lineB);
  clearLine(lineC);
  password = 0;
  len = 0;
  isFirstRead = true;
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
  Serial.println("Advent of Code 2025 Day 4");
  Serial.println("READY");
  resetState();
}

void loop() {
  if(!Serial.available()) return;
  
  char cmd = Serial.peek();
  
  switch (cmd) {
    case 'R':
      Serial.read();
      Serial.println("RESET");
      resetState();
      break;
      
    case 'D':
      Serial.read();
      clearLine(lineC);
      processCurrentLine();
      Serial.print(password);
      Serial.println(".");
      break;
      
    case '.':
    case '@':
      if(isFirstRead) {
        len = readLine(lineB);
        Serial.println('.');
        len = readLine(lineC);
        isFirstRead = false;
      } else {
        len = readLine(lineC);
      }
      
      processCurrentLine();
      shiftBuffers();
      
      Serial.print(password);
      Serial.println(".");
      break;
      
    default:
      Serial.read();
      Serial.println("JUNK");
      break;
  }
}