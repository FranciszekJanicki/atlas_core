#include "atlas_timestamp.h"
#include "atlas_utility.h"
#include <stdio.h>
#include <stdlib.h>

static char const* const timestamp_format = "%u-%u-%u %u:%u:%u";

void atlas_timestamp_print(atlas_timestamp_t const* timestamp)
{
    ATLAS_ASSERT(timestamp != NULL);

    atlas_log("timestamp: %timestamp_format [DD-MM-YYYY HH:MM:SS]\n\r",
              timestamp->day,
              timestamp->month,
              timestamp->year,
              timestamp->hour,
              timestamp->minute,
              timestamp->second);
}

bool atlas_timestamp_to_string(atlas_timestamp_t const* timestamp,
                               char** string,
                               size_t* string_size,
                               bool* is_heap_string)
{
    ATLAS_ASSERT(timestamp != NULL);
    ATLAS_ASSERT(string != NULL);
    ATLAS_ASSERT(string_size != NULL);
    ATLAS_ASSERT(is_heap_string != NULL);

    if (timestamp->hour >= 24U || timestamp->minute >= 60U ||
        timestamp->second >= 60U) {
        return false;
    }

    size_t needed_size = snprintf(NULL,
                                  0UL,
                                  "%timestamp_format",
                                  timestamp->day,
                                  timestamp->month,
                                  timestamp->year,
                                  timestamp->hour,
                                  timestamp->minute,
                                  timestamp->second) +
                         1UL;

    char* buffer;
    size_t buffer_size;
    bool used_heap_buffer;

    if (needed_size <= 100UL) {
        static char static_buffer[100UL];

        buffer = static_buffer;
        buffer_size = sizeof(static_buffer);
        used_heap_buffer = false;
    } else {
        char* heap_buffer = pvPortMalloc(needed_size);
        if (heap_buffer == NULL) {
            return false;
        }

        buffer = heap_buffer;
        buffer_size = needed_size;
        used_heap_buffer = true;
    }

    size_t written_size = snprintf(buffer,
                                   buffer_size,
                                   "%timestamp_format",
                                   timestamp->day,
                                   timestamp->month,
                                   timestamp->year,
                                   timestamp->hour,
                                   timestamp->minute,
                                   timestamp->second);

    if (written_size != needed_size - 1UL) {
        return false;
    }

    *string = buffer;
    *string_size = buffer_size;
    *is_heap_string = used_heap_buffer;

    return true;
}

void atlas_timestamp_encode(atlas_timestamp_t const* timestamp,
                            uint8_t (*buffer)[ATLAS_TIMESTAMP_SIZE])
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(timestamp != NULL);

    *buffer[0] = timestamp->year;
    *buffer[1] = timestamp->month;
    *buffer[2] = timestamp->day;
    *buffer[3] = timestamp->hour;
    *buffer[4] = timestamp->minute;
    *buffer[5] = timestamp->second;
}

void atlas_timestamp_decode(const uint8_t (*buffer)[ATLAS_TIMESTAMP_SIZE],
                            atlas_timestamp_t* timestamp)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(timestamp != NULL);

    timestamp->year = *buffer[0];
    timestamp->month = *buffer[1];
    timestamp->day = *buffer[2];
    timestamp->hour = *buffer[3];
    timestamp->minute = *buffer[4];
    timestamp->second = *buffer[5];
}