#include "atlas_packet.h"
#include "atlas_utility.h"
#include "bitwise.h"
#include "string.h"

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

static inline void atlas_timestamp_encode(atlas_timestamp_t const* timestamp,
                                          uint8_t* buffer)
{
    buffer[0] = timestamp->hours;
    buffer[1] = timestamp->minutes;
    buffer[2] = timestamp->seconds;
}

static inline void atlas_timestamp_decode(uint8_t const* buffer,
                                          atlas_timestamp_t* timestamp)
{
    timestamp->hours = buffer[0];
    timestamp->minutes = buffer[1];
    timestamp->seconds = buffer[2];
}

static inline void atlas_robot_packet_type_encode(
    atlas_robot_packet_type_t type,
    uint8_t* buffer)
{
    uint8x4_t type_buffer = uint32_to_uint8x4_be(type);

    buffer[0] = type_buffer.data[0];
    buffer[1] = type_buffer.data[1];
    buffer[2] = type_buffer.data[2];
    buffer[3] = type_buffer.data[3];
}

static inline void atlas_robot_packet_type_decode(
    uint8_t const* buffer,
    atlas_robot_packet_type_t* type)
{
    uint8x4_t type_buffer;
    type_buffer.data[0] = buffer[0];
    type_buffer.data[1] = buffer[1];
    type_buffer.data[2] = buffer[2];
    type_buffer.data[3] = buffer[3];

    *type = uint8x4_be_to_uint32(type_buffer);
}

static inline void atlas_robot_packet_origin_encode(
    atlas_robot_packet_origin_t origin,
    uint8_t* buffer)
{
    uint8x4_t origin_buffer = uint32_to_uint8x4_be(origin);

    buffer[0] = origin_buffer.data[0];
    buffer[1] = origin_buffer.data[1];
    buffer[2] = origin_buffer.data[2];
    buffer[3] = origin_buffer.data[3];
}

static inline void atlas_robot_packet_origin_decode(
    uint8_t const* buffer,
    atlas_robot_packet_origin_t* origin)
{
    uint8x4_t origin_buffer;
    origin_buffer.data[0] = buffer[0];
    origin_buffer.data[1] = buffer[1];
    origin_buffer.data[2] = buffer[2];
    origin_buffer.data[3] = buffer[3];

    *origin = uint8x4_be_to_uint32(origin_buffer);
}

static inline void atlas_robot_packet_payload_encode(
    atlas_robot_packet_type_t type,
    atlas_robot_packet_payload_t const* payload,
    uint8_t* buffer)
{
    if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_DATA) {
        uint8x4_t position_buffer =
            float32_to_uint8x4_be(payload->joint_data.position);

        buffer[0] = position_buffer.data[0];
        buffer[1] = position_buffer.data[1];
        buffer[2] = position_buffer.data[2];
        buffer[3] = position_buffer.data[3];
    } else if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT) {
    } else if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_READY) {
    }
}

static inline void atlas_robot_packet_payload_decode(
    uint8_t const* buffer,
    atlas_robot_packet_type_t type,
    atlas_robot_packet_payload_t* payload)
{
    if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_DATA) {
        uint8x4_t position_buffer;
        position_buffer.data[0] = buffer[0];
        position_buffer.data[1] = buffer[1];
        position_buffer.data[2] = buffer[2];
        position_buffer.data[3] = buffer[3];

        payload->joint_data.position = uint8x4_be_to_float32(position_buffer);
    } else if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT) {
    } else if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_READY) {
    }
}

void atlas_robot_packet_encode(atlas_robot_packet_t const* packet,
                               uint8_t (*buffer)[ROBOT_PACKET_SIZE])
{
    ATLAS_ASSERT(packet && buffer);

    atlas_timestamp_encode(&packet->timestamp, *buffer);
    atlas_robot_packet_type_encode(packet->type, *buffer + 3);
    atlas_robot_packet_origin_encode(packet->origin, *buffer + 7);
    atlas_robot_packet_payload_encode(packet->type,
                                      &packet->payload,
                                      *buffer + 11);
}

void atlas_robot_packet_decode(const uint8_t (*buffer)[ROBOT_PACKET_SIZE],
                               atlas_robot_packet_t* packet)
{
    ATLAS_ASSERT(packet && buffer);

    atlas_timestamp_decode(*buffer, &packet->timestamp);
    atlas_robot_packet_type_decode(*buffer + 3, &packet->type);
    atlas_robot_packet_origin_decode(*buffer + 7, &packet->origin);
    atlas_robot_packet_payload_decode(*buffer + 11,
                                      packet->type,
                                      &packet->payload);
}

static inline void atlas_joint_packet_type_encode(
    atlas_joint_packet_type_t type,
    uint8_t* buffer)
{
    uint8x4_t type_buffer = uint32_to_uint8x4_be(type);

    buffer[0] = type_buffer.data[0];
    buffer[1] = type_buffer.data[1];
    buffer[2] = type_buffer.data[2];
    buffer[3] = type_buffer.data[3];
}

static inline void atlas_joint_packet_type_decode(
    uint8_t const* buffer,
    atlas_joint_packet_type_t* type)
{
    uint8x4_t type_buffer;
    type_buffer.data[0] = buffer[0];
    type_buffer.data[1] = buffer[1];
    type_buffer.data[2] = buffer[2];
    type_buffer.data[3] = buffer[3];

    *type = uint8x4_be_to_uint32(type_buffer);
}

static inline void atlas_joint_packet_payload_encode(
    atlas_joint_packet_type_t type,
    atlas_joint_packet_payload_t const* payload,
    uint8_t* buffer)
{
    if (type == ATLAS_JOINT_PACKET_TYPE_JOINT_DATA) {
        uint8x4_t position_buffer =
            float32_to_uint8x4_be(payload->joint_data.position);

        buffer[0] = position_buffer.data[0];
        buffer[1] = position_buffer.data[1];
        buffer[2] = position_buffer.data[2];
        buffer[3] = position_buffer.data[3];
    } else if (type == ATLAS_JOINT_PACKET_TYPE_JOINT_START) {
    } else if (type == ATLAS_JOINT_PACKET_TYPE_JOINT_STOP) {
    }
}

static inline void atlas_joint_packet_payload_decode(
    uint8_t const* buffer,
    atlas_joint_packet_type_t type,
    atlas_joint_packet_payload_t* payload)
{
    if (type == ATLAS_JOINT_PACKET_TYPE_JOINT_DATA) {
        uint8x4_t position_buffer;
        position_buffer.data[0] = buffer[0];
        position_buffer.data[1] = buffer[1];
        position_buffer.data[2] = buffer[2];
        position_buffer.data[3] = buffer[3];

        payload->joint_data.position = uint8x4_be_to_float32(position_buffer);
    } else if (type == ATLAS_JOINT_PACKET_TYPE_JOINT_START) {
    } else if (type == ATLAS_JOINT_PACKET_TYPE_JOINT_STOP) {
    }
}

void atlas_joint_packet_encode(atlas_joint_packet_t const* packet,
                               uint8_t (*buffer)[JOINT_PACKET_SIZE])
{
    ATLAS_ASSERT(packet && buffer);

    atlas_timestamp_encode(&packet->timestamp, *buffer);
    atlas_joint_packet_type_encode(packet->type, *buffer + 3);
    atlas_joint_packet_payload_encode(packet->type,
                                      &packet->payload,
                                      *buffer + 7);
}

void atlas_joint_packet_decode(const uint8_t (*buffer)[JOINT_PACKET_SIZE],
                               atlas_joint_packet_t* packet)
{
    ATLAS_ASSERT(buffer && packet);

    atlas_timestamp_decode(*buffer, &packet->timestamp);
    atlas_joint_packet_type_decode(*buffer + 3, &packet->type);
    atlas_joint_packet_payload_decode(*buffer + 7,
                                      packet->type,
                                      &packet->payload);
}
