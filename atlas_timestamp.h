#ifndef ATLAS_CORE_ATLAS_TIMESTAMP_H
#define ATLAS_CORE_ATLAS_TIMESTAMP_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t day;
    uint8_t month;
    uint8_t year;
} atlas_timestamp_t;

#define ATLAS_TIMESTAMP_SIZE (sizeof(atlas_timestamp_t))

void atlas_timestamp_encode_binary(atlas_timestamp_t const* timestamp,
                                   uint8_t (*buffer)[ATLAS_TIMESTAMP_SIZE]);
void atlas_timestamp_decode_binary(
    const uint8_t (*buffer)[ATLAS_TIMESTAMP_SIZE],
    atlas_timestamp_t* timestamp);

void atlas_timestamp_encode_symbolic(atlas_timestamp_t const* timestamp,
                                     char* buffer,
                                     size_t buffer_len);

void atlas_timestamp_decode_symbolic(char const* buffer,
                                     atlas_timestamp_t* timestamp);

#endif // ATLAS_CORE_ATLAS_TIMESTAMP_H
