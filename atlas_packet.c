#include "atlas_packet.h"
#include "atlas_utility.h"
#include "string.h"
#include "utility.h"

// properly encode / decode array of uint8_t into packet struct
// and vice-versa. It is correct even if the layout of these types
// (the whole struct as well as members) is different on MCUs
// communicating using these packet types. No matter endian,
// no matter layout in memory, no matter sizeof and alignof,
// because it is done referring to each field independently
// and working on variable values (which do not change
// no matter endianess) and not done via pointer cast / memcpy / union.
// union / pointer cast / memcpy is good for reinterpreting memory
// when 100% sure about memory layout and endianess, which is not
// the case when sending reinterpreted / reinterpreting received
// bytes between different devices

void atlas_robot_packet_encode(atlas_robot_packet_t const* packet,
                               uint8_t (*buffer)[ROBOT_PACKET_SIZE])
{
    ATLAS_ASSERT(packet && buffer);

    uint8x4_t timestamp = uint32_to_uint8x4_be(packet->timestamp);
    *buffer[0] = timestamp.data[0];
    *buffer[1] = timestamp.data[1];
    *buffer[2] = timestamp.data[2];
    *buffer[3] = timestamp.data[3];

    uint8x4_t type = uint32_to_uint8x4_be(packet->type);
    *buffer[4] = type.data[0];
    *buffer[5] = type.data[1];
    *buffer[6] = type.data[2];
    *buffer[7] = type.data[3];

    uint8x4_t origin = uint32_to_uint8x4_be(packet->origin);
    *buffer[8] = origin.data[0];
    *buffer[9] = origin.data[1];
    *buffer[10] = origin.data[2];
    *buffer[11] = origin.data[3];

    if (packet->type == ATLAS_ROBOT_PACKET_TYPE_JOINT_DATA) {
        uint8x4_t position = uint32_to_uint8x4_be(
            float32_to_uint32(packet->payload.joint_data.position));
        *buffer[12] = position.data[0];
        *buffer[13] = position.data[1];
        *buffer[14] = position.data[2];
        *buffer[15] = position.data[3];
    } else if (packet->type == ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT) {
    } else if (packet->type == ATLAS_ROBOT_PACKET_TYPE_JOINT_READY) {
    }
}

void atlas_robot_packet_decode(const uint8_t (*buffer)[ROBOT_PACKET_SIZE],
                               atlas_robot_packet_t* packet)
{
    ATLAS_ASSERT(buffer && packet);

    uint8x4_t timestamp = {.data[0] = *buffer[0],
                           .data[1] = *buffer[1],
                           .data[2] = *buffer[2],
                           .data[3] = *buffer[3]};
    packet->timestamp = uint8x4_be_to_uint32(timestamp);

    uint8x4_t type = {.data[0] = *buffer[4],
                      .data[1] = *buffer[5],
                      .data[2] = *buffer[6],
                      .data[3] = *buffer[7]};
    packet->type = uint8x4_be_to_uint32(type);

    uint8x4_t origin = {.data[0] = *buffer[8],
                        .data[1] = *buffer[9],
                        .data[2] = *buffer[10],
                        .data[3] = *buffer[11]};
    packet->origin = uint8x4_be_to_uint32(origin);

    if (packet->type == ATLAS_ROBOT_PACKET_TYPE_JOINT_DATA) {
        uint8x4_t position = {.data = {[0] = *buffer[12],
                                       [1] = *buffer[13],
                                       [2] = *buffer[14],
                                       [3] = *buffer[15]}};
        packet->payload.joint_data.position =
            uint32_to_float32(uint8x4_be_to_uint32(position));
    } else if (packet->type == ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT) {
    } else if (packet->type == ATLAS_ROBOT_PACKET_TYPE_JOINT_READY) {
    }
}

void atlas_joint_packet_encode(atlas_joint_packet_t const* packet,
                               uint8_t (*buffer)[JOINT_PACKET_SIZE])
{
    ATLAS_ASSERT(packet && buffer);

    uint8x4_t timestamp = uint32_to_uint8x4_be(packet->timestamp);
    *buffer[0] = timestamp.data[0];
    *buffer[1] = timestamp.data[1];
    *buffer[2] = timestamp.data[2];
    *buffer[3] = timestamp.data[3];

    uint8x4_t type = uint32_to_uint8x4_be(packet->type);
    *buffer[4] = type.data[0];
    *buffer[5] = type.data[1];
    *buffer[6] = type.data[2];
    *buffer[7] = type.data[3];

    if (packet->type == ATLAS_JOINT_PACKET_TYPE_JOINT_DATA) {
        uint8x4_t position = uint32_to_uint8x4_be(
            float32_to_uint32(packet->payload.joint_data.position));
        *buffer[12] = position.data[0];
        *buffer[13] = position.data[1];
        *buffer[14] = position.data[2];
        *buffer[15] = position.data[3];
    } else if (packet->type == ATLAS_JOINT_PACKET_TYPE_JOINT_START) {
    } else if (packet->type == ATLAS_JOINT_PACKET_TYPE_JOINT_STOP) {
    }
}

void atlas_joint_packet_decode(const uint8_t (*buffer)[JOINT_PACKET_SIZE],
                               atlas_joint_packet_t* packet)
{
    ATLAS_ASSERT(buffer && packet);

    uint8x4_t timestamp = {.data[0] = *buffer[0],
                           .data[1] = *buffer[1],
                           .data[2] = *buffer[2],
                           .data[3] = *buffer[3]};
    packet->timestamp = uint8x4_be_to_uint32(timestamp);

    uint8x4_t type = {.data[0] = *buffer[4],
                      .data[1] = *buffer[5],
                      .data[2] = *buffer[6],
                      .data[3] = *buffer[7]};
    packet->type = uint8x4_be_to_uint32(type);

    if (packet->type == ATLAS_JOINT_PACKET_TYPE_JOINT_DATA) {
        uint8x4_t position = {.data = {[0] = *buffer[8],
                                       [1] = *buffer[9],
                                       [2] = *buffer[10],
                                       [3] = *buffer[11]}};
        packet->payload.joint_data.position =
            uint32_to_float32(uint8x4_be_to_uint32(position));
    } else if (packet->type == ATLAS_JOINT_PACKET_TYPE_JOINT_START) {
    } else if (packet->type == ATLAS_JOINT_PACKET_TYPE_JOINT_STOP) {
    }
}
