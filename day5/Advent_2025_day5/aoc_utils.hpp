#pragma once

uint64_t stringToUint64(const char* str) {
  uint64_t result = 0;
  while (*str) {
    if (*str >= '0' && *str <= '9') {
      result = result * 10 + (*str - '0');
    }
    str++;
  }
  return result;
}

void uint64ToString(uint64_t value, char* str) {
  if (value == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }
  
  int i = 0;
  uint64_t temp = value;
  
  while (temp > 0) {
    i++;
    temp /= 10;
  }
  
  str[i] = '\0';
    while (value > 0) {
    str[--i] = '0' + (value % 10);
    value /= 10;
  }
}
