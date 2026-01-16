#include "atlas_log.h"
#include "FreeRTOS.h"
#include "allocator.h"
#include "atlas_utility.h"
#include "stream_buffer.h"
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int _write(int file, char* ptr, int len);

#define STATIC_BUFFER_LEN (1000U)

void atlas_log(char const* format, ...)
{
    ATLAS_ASSERT(format != NULL);

    va_list args;
    va_start(args, format);
    int needed_len = vsnprintf(NULL, 0UL, format, args) + 2;
    va_end(args);

    char* buffer;
    size_t buffer_len;
    bool used_heap_buffer;

    if (needed_len <= STATIC_BUFFER_LEN) {
        static char static_buffer[STATIC_BUFFER_LEN];
        taskENTER_CRITICAL();

        buffer = static_buffer;
        buffer_len = STATIC_BUFFER_LEN;
        used_heap_buffer = false;
    } else {
        char* heap_buffer = ATLAS_MALLOC(needed_len);
        if (heap_buffer == NULL) {
            return;
        }

        buffer = heap_buffer;
        buffer_len = (size_t)needed_len;
        used_heap_buffer = true;
    }

    memset(buffer, 0, buffer_len);

    va_start(args, format);
    int written_len = vsnprintf(buffer, buffer_len, format, args);
    va_end(args);

    if (written_len < 0 || written_len != needed_len - 2) {
        if (used_heap_buffer) {
            ATLAS_FREE(buffer);
        } else {
            taskEXIT_CRITICAL();
        }

        return;
    }

    buffer[written_len] = '\0';

    if (strncmp(buffer + written_len - 2,
                "\n\r",
                buffer_len - written_len + 2) != 0) {
        if (strncat(buffer, "\n\r", buffer_len - written_len + 2)) {
            written_len += 2;
        }
    }

    _write(1, buffer, written_len);

    if (used_heap_buffer) {
        ATLAS_FREE(buffer);
    } else {
        taskEXIT_CRITICAL();
    }
}

#undef STATIC_BUFFER_LEN
