#include "atlas_log.h"
#include "FreeRTOS.h"
#include "allocator.h"
#include "stream_buffer.h"
#include "usart.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int _write(int file, char* ptr, int len);

void atlas_log(char const* format, ...)
{
    va_list args;

    va_start(args, format);
    size_t buffer_len = vsnprintf(NULL, 0UL, format, args) + 1UL;
    va_end(args);

    allocator_t allocator;
    char* buffer = allocator_new(&allocator, buffer_len);
    if (!buffer) {
        return;
    }

    va_start(args, format);
    size_t written_len = vsnprintf(buffer, buffer_len, format, args);
    va_end(args);

    if (written_len == buffer_len - 1UL) {
        _write(0, buffer, strlen(buffer));
    }

    allocator_delete(&allocator);
}
