#ifndef ATLAS_CORE_ATLAS_CRC_H
#define ATLAS_CORE_ATLAS_CRC_H

#include "atlas_packet.h"

typedef uint32_t atlas_crc_t;

atlas_crc_t atlas_crc_calculate_robot_packet(
    const uint8_t (*packet)[ROBOT_PACKET_SIZE]);

atlas_crc_t atlas_crc_calculate_joint_packet(
    const uint8_t (*packet)[JOINT_PACKET_SIZE]);

#endif // ATLAS_CORE_ATLAS_CRC_H