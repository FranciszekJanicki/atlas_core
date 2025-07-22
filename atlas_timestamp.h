#ifndef ATLAS_CORE_ATLAS_TIMESTAMP_H
#define ATLAS_CORE_ATLAS_TIMESTAMP_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} atlas_timestamp_t;

void atlas_timestamp_print(atlas_timestamp_t const* timestamp);

bool atlas_timestamp_to_string(atlas_timestamp_t const* timestamp,
                               char** data,
                               size_t* data_size,
                               bool* used_malloc);

#endif // ATLAS_CORE_ATLAS_TIMESTAMP_H
