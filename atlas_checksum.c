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