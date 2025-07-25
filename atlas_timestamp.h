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

void atlas_timestamp_print(atlas_timestamp_t const* timestamp);

bool atlas_timestamp_to_string(atlas_timestamp_t const* timestamp,
                               char** string,
                               size_t* string_size,
                               bool* is_heap_string);

#endif // ATLAS_CORE_ATLAS_TIMESTAMP_H
