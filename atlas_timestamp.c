#include "atlas_timestamp.h"
#include "atlas_utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void atlas_timestamp_encode_binary(atlas_timestamp_t const* timestamp,
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

void atlas_timestamp_decode_binary(
    const uint8_t (*buffer)[ATLAS_TIMESTAMP_SIZE],
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

void atlas_timestamp_encode_symbolic(atlas_timestamp_t const* timestamp,
                                     char* buffer,
                                     size_t buffer_len)
{
    ATLAS_ASSERT(timestamp != NULL);
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(buffer_len > 0UL);

    ATLAS_ASSERT(timestamp->hour < 24U && timestamp->hour >= 0U);
    ATLAS_ASSERT(timestamp->minute < 60U && timestamp->minute >= 0U);
    ATLAS_ASSERT(timestamp->second < 60U && timestamp->second >= 0U);

    int written_len = snprintf(buffer,
                               buffer_len - 1U,
                               "%u-%u-%u %u:%u:%u",
                               timestamp->day,
                               timestamp->month,
                               timestamp->year,
                               timestamp->hour,
                               timestamp->minute,
                               timestamp->second);
    buffer[written_len] = '\0';
}

void atlas_timestamp_decode_symbolic(char const* buffer,
                                     atlas_timestamp_t* timestamp)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(strlen(buffer) > 0UL);
    ATLAS_ASSERT(timestamp != NULL);
}
