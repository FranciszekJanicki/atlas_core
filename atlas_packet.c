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
    if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_MEASURE) {
        uint8x4_t position_buffer =
            float32_to_uint8x4_be(payload->joint_measure.position);

        buffer[0] = position_buffer.data[0];
        buffer[1] = position_buffer.data[1];
        buffer[2] = position_buffer.data[2];
        buffer[3] = position_buffer.data[3];

        uint8x4_t current_buffer =
            float32_to_uint8x4_be(payload->joint_measure.current);

        buffer[0] = current_buffer.data[0];
        buffer[1] = current_buffer.data[1];
        buffer[2] = current_buffer.data[2];
        buffer[3] = current_buffer.data[3];
    } else if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT) {
    } else if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_READY) {
    }
}

static inline void atlas_robot_packet_payload_decode(
    uint8_t const* buffer,
    atlas_robot_packet_type_t type,
    atlas_robot_packet_payload_t* payload)
{
    if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_MEASURE) {
        uint8x4_t position_buffer;
        position_buffer.data[0] = buffer[0];
        position_buffer.data[1] = buffer[1];
        position_buffer.data[2] = buffer[2];
        position_buffer.data[3] = buffer[3];

        payload->joint_measure.position =
            uint8x4_be_to_float32(position_buffer);

        uint8x4_t current_buffer;
        current_buffer.data[0] = buffer[0];
        current_buffer.data[1] = buffer[1];
        current_buffer.data[2] = buffer[2];
        current_buffer.data[3] = buffer[3];

        payload->joint_measure.current = uint8x4_be_to_float32(current_buffer);
    } else if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT) {
    } else if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_READY) {
    }
}

void atlas_robot_packet_encode(atlas_robot_packet_t const* packet,
                               uint8_t (*buffer)[ATLAS_ROBOT_PACKET_SIZE])
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* type_buffer = *buffer;
    atlas_robot_packet_type_encode(packet->type, type_buffer);

    uint8_t* origin_buffer = type_buffer + sizeof(atlas_robot_packet_type_t);
    atlas_robot_packet_origin_encode(packet->origin, origin_buffer);

    uint8_t* payload_buffer =
        origin_buffer + sizeof(atlas_robot_packet_origin_t);
    atlas_robot_packet_payload_encode(packet->type,
                                      &packet->payload,
                                      payload_buffer);

    uint8_t* timestamp_buffer =
        payload_buffer + sizeof(atlas_robot_packet_payload_t);
    atlas_timestamp_encode(&packet->timestamp,
                           (uint8_t (*)[ATLAS_TIMESTAMP_SIZE])timestamp_buffer);

    uint8_t* checksum_buffer = timestamp_buffer + sizeof(atlas_timestamp_t);
    atlas_checksum_encode(&packet->checksum,
                          (uint8_t (*)[ATLAS_CHECKSUM_SIZE])checksum_buffer);
}

void atlas_robot_packet_decode(const uint8_t (*buffer)[ATLAS_ROBOT_PACKET_SIZE],
                               atlas_robot_packet_t* packet)
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* type_buffer = *buffer;
    atlas_robot_packet_type_decode(type_buffer, &packet->type);

    uint8_t* origin_buffer = type_buffer + sizeof(atlas_robot_packet_type_t);
    atlas_robot_packet_origin_decode(origin_buffer, &packet->origin);

    uint8_t* payload_buffer =
        origin_buffer + sizeof(atlas_robot_packet_origin_t);
    atlas_robot_packet_payload_decode(payload_buffer,
                                      packet->type,
                                      &packet->payload);

    uint8_t* timestamp_buffer =
        payload_buffer + sizeof(atlas_robot_packet_origin_t);
    atlas_timestamp_decode((uint8_t (*)[ATLAS_TIMESTAMP_SIZE])timestamp_buffer,
                           &packet->timestamp);

    uint8_t* checksum_buffer = timestamp_buffer + sizeof(atlas_timestamp_t);
    atlas_checksum_decode((uint8_t (*)[ATLAS_CHECKSUM_SIZE])checksum_buffer,
                          &packet->checksum);
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
    if (type == ATLAS_JOINT_PACKET_TYPE_JOINT_REFERENCE) {
        uint8x4_t position_buffer =
            float32_to_uint8x4_be(payload->joint_reference.position);

        buffer[0] = position_buffer.data[0];
        buffer[1] = position_buffer.data[1];
        buffer[2] = position_buffer.data[2];
        buffer[3] = position_buffer.data[3];

        uint8x4_t delta_time_buffer =
            float32_to_uint8x4_be(payload->joint_reference.delta_time);

        buffer[4] = delta_time_buffer.data[0];
        buffer[5] = delta_time_buffer.data[1];
        buffer[6] = delta_time_buffer.data[2];
        buffer[7] = delta_time_buffer.data[3];
    } else if (type == ATLAS_JOINT_PACKET_TYPE_JOINT_START) {
    } else if (type == ATLAS_JOINT_PACKET_TYPE_JOINT_STOP) {
    }
}

static inline void atlas_joint_packet_payload_decode(
    uint8_t const* buffer,
    atlas_joint_packet_type_t type,
    atlas_joint_packet_payload_t* payload)
{
    if (type == ATLAS_JOINT_PACKET_TYPE_JOINT_REFERENCE) {
        uint8x4_t position_buffer;
        position_buffer.data[0] = buffer[0];
        position_buffer.data[1] = buffer[1];
        position_buffer.data[2] = buffer[2];
        position_buffer.data[3] = buffer[3];

        payload->joint_reference.position =
            uint8x4_be_to_float32(position_buffer);

        uint8x4_t delta_time_buffer;
        delta_time_buffer.data[0] = buffer[4];
        delta_time_buffer.data[1] = buffer[5];
        delta_time_buffer.data[2] = buffer[6];
        delta_time_buffer.data[3] = buffer[7];

        payload->joint_reference.delta_time =
            uint8x4_be_to_float32(delta_time_buffer);
    } else if (type == ATLAS_JOINT_PACKET_TYPE_JOINT_START) {
    } else if (type == ATLAS_JOINT_PACKET_TYPE_JOINT_STOP) {
    }
}

void atlas_joint_packet_encode(atlas_joint_packet_t const* packet,
                               uint8_t (*buffer)[ATLAS_JOINT_PACKET_SIZE])
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* type_buffer = *buffer;
    atlas_joint_packet_type_encode(packet->type, type_buffer);

    uint8_t* payload_buffer = type_buffer + sizeof(atlas_joint_packet_type_t);
    atlas_joint_packet_payload_encode(packet->type,
                                      &packet->payload,
                                      payload_buffer);

    uint8_t* timestamp_buffer =
        payload_buffer + sizeof(atlas_joint_packet_payload_t);
    atlas_timestamp_encode(&packet->timestamp,
                           (uint8_t (*)[ATLAS_TIMESTAMP_SIZE])timestamp_buffer);

    uint8_t* checksum_buffer = timestamp_buffer + sizeof(atlas_timestamp_t);
    atlas_checksum_encode(&packet->checksum,
                          (uint8_t (*)[ATLAS_CHECKSUM_SIZE])checksum_buffer);
}

void atlas_joint_packet_decode(const uint8_t (*buffer)[ATLAS_JOINT_PACKET_SIZE],
                               atlas_joint_packet_t* packet)
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* type_buffer = *buffer;
    atlas_joint_packet_type_decode(type_buffer, &packet->type);

    uint8_t* payload_buffer = type_buffer + sizeof(atlas_joint_packet_type_t);
    atlas_joint_packet_payload_decode(payload_buffer,
                                      packet->type,
                                      &packet->payload);

    uint8_t* timestamp_buffer =
        payload_buffer + sizeof(atlas_joint_packet_payload_t);
    atlas_timestamp_decode((uint8_t (*)[ATLAS_TIMESTAMP_SIZE])timestamp_buffer,
                           &packet->timestamp);

    uint8_t* checksum_buffer = timestamp_buffer + sizeof(atlas_timestamp_t);
    atlas_checksum_decode((uint8_t (*)[ATLAS_CHECKSUM_SIZE])checksum_buffer,
                          &packet->checksum);
}
