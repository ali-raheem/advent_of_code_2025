#pragma once

template <typename T>
T reduce(T (*op)(T, T), const T* data, int len) {
    if (len == 0) return T(0);
    T res = data[0];
    for (int i = 1; i < len; i++) {
        res = op(res, data[i]);
    }
    return res;
}

template <typename T>
void map(T (*op)(T), T* data, int len) {
    for (int i = 0; i < len; i++)
        data[i] = op(data[i]);
}

template <typename T, typename U>
void map(U (*op)(T), const T* data, U* out, int len) {
    for (int i = 0; i < len; i++) {
        out[i] = op(data[i]);
    }
}

template <typename T>
bool any(bool (*pred)(T), const T* list, int len) {
    for (int i = 0; i < len; i++) {
        if (pred(list[i]))
            return true;
    }
    return false;
}

template <typename T>
bool all(bool (*pred)(T), const T* list, int len) {
    for (int i = 0; i < len; i++)
        if (!pred(list[i]))
            return false;
    return true;
}

template <typename T>
int filter(bool (*pred)(T), const T* list, T* out, int len) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (pred(list[i]))
            out[count++] = list[i];
    }
    return count;
}

template <typename T, typename U>
void zip(U (*op)(T, T), const T* a, const T* b, U* c, int len) {
    for (int i = 0; i < len; i++) {
        c[i] = op(a[i], b[i]);
    }
}

template <typename T>
void forEach(void (*op)(T), const T* list, int len) {
    for (int i = 0; i < len; i++) {
        op(list[i]);
    }
}

template <typename T>
int first(bool (*pred)(T), const T* list, int len) {
    for (int i = 0; i < len; i++) {
        if (pred(list[i]))
            return i;
    }
    return -1;
}

template <typename T>
int count(bool (*pred)(T), const T* list, int len) {
    int total = 0;
    for (int i = 0; i < len; i++) {
        if (pred(list[i]))
            total++;
    }
    return total;
}

template <typename T>
bool none(bool (*pred)(T), const T* list, int len) {
    return !any(pred, list, len);
}

template <typename T>
T add(T x, T y) {
    return x + y;
}

template <typename T>
T mul(T x, T y) {
    return x * y;
}

template <typename T>
T sub(T x, T y) {
    return x - y;
}

template <typename T>
T div(T x, T y) {
    return y == T(0) ? T(0) : x / y;
}

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