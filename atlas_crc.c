#include "atlas_crc.h"
#include "atlas_utility.h"
#include "utility.h"

atlas_crc_t atlas_crc_calculate_robot_packet(
    const uint8_t (*packet)[ROBOT_PACKET_SIZE])
{
    ATLAS_ASSERT(packet != NULL);

    return uint32_calculate_crc(*packet,
                                sizeof(*packet),
                                0x00,
                                0x00,
                                0x00,
                                false,
                                false);
}

atlas_crc_t atlas_crc_calculate_joint_packet(
    const uint8_t (*packet)[JOINT_PACKET_SIZE])
{
    ATLAS_ASSERT(packet != NULL);

    return uint32_calculate_crc(*packet,
                                sizeof(*packet),
                                0x00,
                                0x00,
                                0x00,
                                false,
                                false);
}
