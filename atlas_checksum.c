#include "atlas_checksum.h"
#include "atlas_utility.h"
#include "utility.h"

void atlas_checksum_calculate(uint8_t const* data,
                              size_t data_size,
                              atlas_checksum_t* checksum)
{
    ATLAS_ASSERT(data != NULL);
    ATLAS_ASSERT(data_size > 0UL);
    ATLAS_ASSERT(checksum != NULL);

    *checksum =
        uint32_calculate_crc(data, data_size, 0x00, 0x00, 0x00, false, false);
}

void atlas_checksum_encode(atlas_checksum_t const* checksum,
                           uint8_t (*buffer)[ATLAS_CHECKSUM_SIZE])
{
    ATLAS_ASSERT(checksum != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8x4_t checksum_buffer = uint32_to_uint8x4_be(*checksum);

    *buffer[0] = checksum_buffer.data[0];
    *buffer[1] = checksum_buffer.data[1];
    *buffer[2] = checksum_buffer.data[2];
    *buffer[3] = checksum_buffer.data[3];
}

void atlas_checksum_decode(const uint8_t (*buffer)[ATLAS_CHECKSUM_SIZE],
                           atlas_checksum_t* checksum)
{
    ATLAS_ASSERT(checksum != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8x4_t checksum_buffer;
    checksum_buffer.data[0] = *buffer[0];
    checksum_buffer.data[1] = *buffer[1];
    checksum_buffer.data[2] = *buffer[2];
    checksum_buffer.data[3] = *buffer[3];

    *checksum = uint8x4_be_to_uint32(checksum_buffer);
}

void atlas_checksum_print(atlas_checksum_t const* checksum)
{
    ATLAS_ASSERT(checksum != NULL);

    atlas_log("Checksum: %u\n\r", *checksum);
}