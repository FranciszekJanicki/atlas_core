#ifndef ATLAS_CORE_ATLAS_CHECKSUM_H
#define ATLAS_CORE_ATLAS_CHECKSUM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef uint32_t atlas_checksum_t;

#define ATLAS_CHECKSUM_SIZE (sizeof(uint32_t))

void atlas_checksum_calculate(uint8_t const* data,
                              size_t data_size,
                              atlas_checksum_t* checksum);

void atlas_checksum_encode(atlas_checksum_t const* checksum,
                           uint8_t (*buffer)[ATLAS_CHECKSUM_SIZE]);
void atlas_checksum_decode(const uint8_t (*buffer)[ATLAS_CHECKSUM_SIZE],
                           atlas_checksum_t* checksum);

void atlas_checksum_to_string(atlas_checksum_t const* checksum,
                              char* buffer,
                              size_t buffer_len);

#endif // ATLAS_CORE_ATLAS_CHECKSUM_H