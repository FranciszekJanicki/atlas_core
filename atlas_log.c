#include "atlas_log.h"
#include "FreeRTOS.h"
#include "allocator.h"
#include "atlas_utility.h"
#include "stream_buffer.h"
#include "usart.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int _write(int file, char* ptr, int len);

#define STATIC_BUFFER_SIZE (1000U)

void atlas_log(char const* format, ...)
{
    ATLAS_ASSERT(format != NULL);

    va_list args;

    va_start(args, format);
    size_t needed_size = vsnprintf(NULL, 0UL, format, args) + 1UL;
    va_end(args);

    char* buffer;
    size_t buffer_size;
    bool used_heap_buffer;

    if (needed_size <= STATIC_BUFFER_SIZE) {
        static char static_buffer[STATIC_BUFFER_SIZE];

        buffer = static_buffer;
        buffer_size = sizeof(static_buffer);
        used_heap_buffer = false;
    } else {
        char* heap_buffer = pvPortMalloc(needed_size);
        if (!heap_buffer) {
            return;
        }

        buffer = heap_buffer;
        buffer_size = needed_size;
        used_heap_buffer = true;
    }

    va_start(args, format);
    size_t written_size = vsnprintf(buffer, buffer_size, format, args);
    va_end(args);

    if (written_size != needed_size - 1UL) {
        return;
    }

    _write(0, buffer, strlen(buffer));

    if (used_heap_buffer) {
        vPortFree(used_heap_buffer);
    }
}

#undef STATIC_BUFFER_SIZE