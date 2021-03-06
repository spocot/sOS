#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static bool print(const char *data, size_t len)
{
    const unsigned char *bytes = (const unsigned char*) data;
    for (size_t i = 0; i < len; i++) {
        if (putchar(bytes[i]) == EOF) {
                return false;
        }
    }
    return true;
}

int printf(const char* restrict format, ...)
{
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0') {
        size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%') {
                ++format;
            }
            size_t amount = 1;
            while (format[amount] && format[amount] != '%') {
                ++amount;
            }
            if (maxrem < amount) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, amount)) {
                return -1;
            }
            format += amount;
            written += amount;
            continue;
        }

        const char *format_begun_at = format++;

        if (*format == 'c') {
            ++format;
            char c = (char) va_arg(parameters, int /* char promotes to int */);
            if (!maxrem) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(&c, sizeof(c))) {
                return -1;
            }
            ++written;
        } else if (*format == 's') {
            ++format;
            const char *str = va_arg(parameters, const char*);
            size_t slen = strlen(str);
            if (maxrem < slen) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(str, slen)) {
                return -1;
            }
            written += slen;
        } else if (*format == 'd') {
            ++format;
            int val = va_arg(parameters, int);
            int i = val;
            size_t digits;
            for (digits = 1; i >= 10; digits++) {
                i = i / 10;
            }
            if (maxrem < digits) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            char s[digits];
            int count;
            i = val;
            for (count = digits - 1; count >= 0; count--) {
                s[count] = (char)((i % 10) + 48);
                i /= 10;
            }
            if (!print(s, digits)) {
                return -1;
            }
            written += digits;
        } else {
            format = format_begun_at;
            size_t slen = strlen(format);
            if (maxrem < slen) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, slen)) {
                return -1;
            }
            written += slen;
            format += slen;
        }
    }

    va_end(parameters);
    return written;
}
