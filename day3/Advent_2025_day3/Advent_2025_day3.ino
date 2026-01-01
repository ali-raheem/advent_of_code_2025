constexpr int BUFFER_LEN = 128;
uint32_t password, a, b = 0;
int a_i, b_i = -1;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
  Serial.println("Advent of Code 2025 Day 3");
  Serial.println("READY");
}

void loop() {
  if(Serial.available()) {
    char first = Serial.peek();
    if(first == 'R') {
      Serial.read();
      Serial.println("RESET");
      a = b = password = 0;
      a_i = b_i = -1;
      return;
    }
    
    char readBuffer[BUFFER_LEN];
    
    int len = Serial.readBytesUntil('\n', readBuffer, BUFFER_LEN - 1);
    readBuffer[len] = '\0';
    int i;
    a = b = 0;
    a_i = b_i = -1;
    for (i = 0; i < len; i++) {
      char c = readBuffer[i];
      if (c < '0' || c > '9')
        continue;
      c -= '0';
      if (c > a) {
        b = a;
        b_i = a_i;
        a = c;
        a_i = i;
      }
    }
    if (a_i == len - 1) {
      //Serial.println("Backwards");
      //Serial.println(b*10 + a);
      password += b*10 + a;
    } else {
      b = 0;
      for (i = a_i + 1; i < len; i++) {
        char c = readBuffer[i];
        if (c < '0' || c > '9')
          continue;
        c -= '0';
        if (c > b) {
          b = c;
          b_i = i;
        }
      }
      password += a*10 + b;
      //Serial.println("Forwards");
      //Serial.println(a*10 + b);
    }
    Serial.print(password);
    Serial.println("DONE");
  }
}