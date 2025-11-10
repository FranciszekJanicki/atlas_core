#include "atlas_packet.h"
#include "atlas_utility.h"
#include <string.h>
#include "utility.h"

static inline void atlas_robot_packet_type_encode_binary(
    atlas_robot_packet_type_t type,
    uint8_t* buffer)
{
    uint8x4_t type_buffer = uint32_to_uint8x4_be(type);
    buffer[0] = type_buffer.data[0];
    buffer[1] = type_buffer.data[1];
    buffer[2] = type_buffer.data[2];
    buffer[3] = type_buffer.data[3];
}

static inline void atlas_robot_packet_type_decode_binary(
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

static inline void atlas_robot_packet_origin_encode_binary(
    atlas_robot_packet_origin_t origin,
    uint8_t* buffer)
{
    uint8x4_t origin_buffer = uint32_to_uint8x4_be(origin);
    buffer[0] = origin_buffer.data[0];
    buffer[1] = origin_buffer.data[1];
    buffer[2] = origin_buffer.data[2];
    buffer[3] = origin_buffer.data[3];
}

static inline void atlas_robot_packet_origin_decode_binary(
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

static inline void atlas_robot_packet_payload_joint_response_encode_binary(
    atlas_robot_packet_payload_joint_response_t const* joint_response,
    uint8_t* buffer)
{}

static inline void atlas_robot_packet_payload_encode_binary(
    atlas_robot_packet_type_t type,
    atlas_robot_packet_payload_t const* payload,
    uint8_t* buffer)
{
    switch (type) {
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_RESPONSE: {
            atlas_robot_packet_payload_joint_response_encode_binary(
                &payload->joint_response,
                buffer);
        } break;
        default: {
        } break;
    }
}

static inline void atlas_robot_packet_payload_joint_response_decode_binary(
    uint8_t const* buffer,
    atlas_robot_packet_payload_joint_response_t* joint_response)
{}

static inline void atlas_robot_packet_payload_decode_binary(
    uint8_t const* buffer,
    atlas_robot_packet_type_t type,
    atlas_robot_packet_payload_t* payload)
{
    switch (type) {
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_RESPONSE: {
            atlas_robot_packet_payload_joint_response_decode_binary(
                buffer,
                &payload->joint_response);
        } break;
        default: {
        } break;
    }
}

static inline void atlas_robot_packet_timestamp_encode_binary(
    atlas_robot_packet_timestamp_t const* timestamp,
    uint8_t* buffer)
{
    atlas_timestamp_encode_binary(timestamp,
                           (uint8_t (*)[ATLAS_TIMESTAMP_SIZE])buffer);
}

static inline void atlas_robot_packet_timestamp_decode_binary(
    uint8_t const* buffer,
    atlas_robot_packet_timestamp_t* timestamp)
{
    atlas_timestamp_decode_binary(
        (const uint8_t (*)[ATLAS_TIMESTAMP_SIZE])buffer,
        timestamp);
}

static inline void atlas_robot_packet_checksum_encode_binary(
    atlas_robot_packet_checksum_t const* checksum,
    uint8_t* buffer)
{
    atlas_checksum_encode_binary(checksum, (uint8_t (*)[ATLAS_CHECKSUM_SIZE])buffer);
}

static inline void atlas_robot_packet_checksum_decode_binary(
    uint8_t const* buffer,
    atlas_robot_packet_checksum_t* checksum)
{
    atlas_checksum_decode_binary((const uint8_t (*)[ATLAS_CHECKSUM_SIZE])buffer,
                                 checksum);
}

static inline void atlas_robot_packet_checksum_calculate(
    uint8_t const* buffer,
    atlas_robot_packet_checksum_t* checksum)
{
    atlas_checksum_encode_binary(checksum, (uint8_t (*)[ATLAS_CHECKSUM_SIZE])buffer);
}

void atlas_robot_packet_encode_binary(atlas_robot_packet_t const* packet,
                               uint8_t (*buffer)[ATLAS_ROBOT_PACKET_SIZE])
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* type_buffer = *buffer + ATLAS_ROBOT_PACKET_TYPE_OFFSET;
    atlas_robot_packet_type_encode_binary(packet->type, type_buffer);

    uint8_t* origin_buffer = *buffer + ATLAS_ROBOT_PACKET_ORIGIN_OFFSET;
    atlas_robot_packet_origin_encode_binary(packet->origin, origin_buffer);

    uint8_t* payload_buffer = *buffer + ATLAS_ROBOT_PACKET_PAYLOAD_OFFSET;
    atlas_robot_packet_payload_encode_binary(packet->type,
                                      &packet->payload,
                                      payload_buffer);

    uint8_t* timestamp_buffer = *buffer + ATLAS_ROBOT_PACKET_TIMESTAMP_OFFSET;
    atlas_robot_packet_timestamp_encode_binary(&packet->timestamp, timestamp_buffer);
}

void atlas_robot_packet_decode_binary(
    const uint8_t (*buffer)[ATLAS_ROBOT_PACKET_SIZE],
    atlas_robot_packet_t* packet)
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* type_buffer = *buffer + ATLAS_ROBOT_PACKET_TYPE_OFFSET;
    atlas_robot_packet_type_decode_binary(type_buffer, &packet->type);

    uint8_t* origin_buffer = *buffer + ATLAS_ROBOT_PACKET_ORIGIN_OFFSET;
    atlas_robot_packet_origin_decode_binary(origin_buffer, &packet->origin);

    uint8_t* payload_buffer = *buffer + ATLAS_ROBOT_PACKET_PAYLOAD_OFFSET;
    atlas_robot_packet_payload_decode_binary(payload_buffer,
                                             packet->type,
                                             &packet->payload);

    uint8_t* timestamp_buffer = *buffer + ATLAS_ROBOT_PACKET_TIMESTAMP_OFFSET;
    atlas_robot_packet_timestamp_decode_binary(timestamp_buffer,
                                               &packet->timestamp);
}

static inline void atlas_joint_packet_type_encode_binary(
    atlas_joint_packet_type_t type,
    uint8_t* buffer)
{
    uint8x4_t type_buffer = uint32_to_uint8x4_be(type);
    buffer[0] = type_buffer.data[0];
    buffer[1] = type_buffer.data[1];
    buffer[2] = type_buffer.data[2];
    buffer[3] = type_buffer.data[3];
}

static inline void atlas_joint_packet_type_decode_binary(
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

static inline void atlas_joint_packet_payload_destination_encode_binary(
    atlas_joint_packet_destination_t destination,
    uint8_t* buffer)
{
    uint8x4_t destination_buffer = uint32_to_uint8x4_be(destination);
    buffer[0] = destination_buffer.data[0];
    buffer[1] = destination_buffer.data[1];
    buffer[2] = destination_buffer.data[2];
    buffer[3] = destination_buffer.data[3];
}

static inline void atlas_joint_packet_payload_destination_decode_binary(
    uint8_t const* buffer,
    atlas_joint_packet_destination_t* destination)
{
    uint8x4_t destination_buffer;
    destination_buffer.data[0] = buffer[0];
    destination_buffer.data[1] = buffer[1];
    destination_buffer.data[2] = buffer[2];
    destination_buffer.data[3] = buffer[3];
    *destination = uint8x4_be_to_uint32(destination_buffer);
}

static inline void atlas_joint_packet_payload_joint_command_encode_binary(
    atlas_joint_packet_payload_joint_command_t const* joint_command,
    uint8_t* buffer)

{
    atlas_joint_command_encode_binary(joint_command,
                               (uint8_t (*)[ATLAS_JOINT_COMMAND_SIZE])buffer);
}

static inline void atlas_joint_packet_payload_joint_command_decode_binary(
    uint8_t* buffer,
    atlas_joint_packet_payload_joint_command_t* joint_command)
{
    atlas_joint_command_decode_binary(
        (const uint8_t (*)[ATLAS_JOINT_COMMAND_SIZE])buffer,
        joint_command);
}

static inline void atlas_joint_packet_payload_encode_binary(
    atlas_joint_packet_type_t type,
    atlas_joint_packet_payload_t const* payload,
    uint8_t* buffer)
{
    switch (type) {
        case ATLAS_JOINT_PACKET_TYPE_JOINT_COMMAND: {
            atlas_joint_packet_payload_joint_command_encode_binary(
                &payload->joint_command,
                buffer);
        } break;
        default: {
        } break;
    }
}

static inline void atlas_joint_packet_payload_decode_binary(
    uint8_t const* buffer,
    atlas_joint_packet_type_t type,
    atlas_joint_packet_payload_t* payload)
{
    switch (type) {
        case ATLAS_JOINT_PACKET_TYPE_JOINT_COMMAND: {
            atlas_joint_packet_payload_joint_command_decode_binary(
                buffer,
                &payload->joint_command);
        } break;
        default: {
        } break;
    }
}

static inline void atlas_joint_packet_timestamp_encode_binary(
    atlas_joint_packet_timestamp_t const* timestamp,
    uint8_t* buffer)
{
    atlas_timestamp_encode_binary(timestamp,
                           (uint8_t (*)[ATLAS_TIMESTAMP_SIZE])buffer);
}

static inline void atlas_joint_packet_timestamp_decode_binary(
    uint8_t const* buffer,
    atlas_joint_packet_timestamp_t* timestamp)
{
    atlas_timestamp_decode_binary(
        (const uint8_t (*)[ATLAS_TIMESTAMP_SIZE])buffer,
        timestamp);
}

static inline void atlas_joint_packet_checksum_encode_binary(
    atlas_joint_packet_checksum_t const* checksum,
    uint8_t* buffer)
{
    atlas_checksum_encode_binary(checksum, (uint8_t (*)[ATLAS_CHECKSUM_SIZE])buffer);
}

static inline void atlas_joint_packet_checksum_decode_binary(
    uint8_t const* buffer,
    atlas_joint_packet_checksum_t* checksum)
{
    atlas_checksum_decode_binary((const uint8_t (*)[ATLAS_CHECKSUM_SIZE])buffer,
                                 checksum);
}

static inline void atlas_joint_packet_checksum_calculate(
    uint8_t const* buffer,
    atlas_joint_packet_checksum_t* checksum)
{
    atlas_checksum_encode_binary(checksum, (uint8_t (*)[ATLAS_CHECKSUM_SIZE])buffer);
}

void atlas_robot_packet_encode_binary_with_checksum(
    atlas_robot_packet_t const* packet,
    uint8_t (*buffer)[ATLAS_ROBOT_PACKET_WITH_CHECKSUM_SIZE])
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* packet_buffer = *buffer;
    atlas_robot_packet_encode_binary(
        packet,
        (uint8_t (*)[ATLAS_ROBOT_PACKET_SIZE])packet_buffer);

    atlas_robot_packet_checksum_t checksum;
    atlas_robot_packet_checksum_calculate(packet_buffer, &checksum);

    uint8_t* checksum_buffer = *buffer + ATLAS_ROBOT_PACKET_CHECKSUM_OFFSET;
    atlas_robot_packet_checksum_encode_binary(&checksum, checksum_buffer);
}

void atlas_robot_packet_decode_binary_with_checksum(
    const uint8_t (*buffer)[ATLAS_ROBOT_PACKET_WITH_CHECKSUM_SIZE],
    atlas_robot_packet_t* packet)
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* packet_buffer = *buffer;
    atlas_robot_packet_decode_binary(
        (const uint8_t (*)[ATLAS_ROBOT_PACKET_SIZE])packet_buffer,
        packet);

    atlas_robot_packet_checksum_t calculated_checksum, received_checksum;
    atlas_robot_packet_checksum_calculate(packet_buffer, &calculated_checksum);

    uint8_t* checksum_buffer = *buffer + ATLAS_ROBOT_PACKET_CHECKSUM_OFFSET;
    atlas_robot_packet_checksum_decode_binary(checksum_buffer,
                                              &received_checksum);

    if (received_checksum != calculated_checksum) {
        atlas_log("Robot packet checksum mismatch!\n\r");
    }
}

void atlas_joint_packet_encode_binary(atlas_joint_packet_t const* packet,
                               uint8_t (*buffer)[ATLAS_JOINT_PACKET_SIZE])
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* type_buffer = *buffer + ATLAS_JOINT_PACKET_TYPE_OFFSET;
    atlas_joint_packet_type_encode_binary(packet->type, type_buffer);

    uint8_t* payload_buffer = *buffer + ATLAS_JOINT_PACKET_PAYLOAD_OFFSET;
    atlas_joint_packet_payload_encode_binary(packet->type,
                                      &packet->payload,
                                      payload_buffer);

    uint8_t* timestamp_buffer = *buffer + ATLAS_JOINT_PACKET_TIMESTAMP_OFFSET;
    atlas_joint_packet_timestamp_encode_binary(&packet->timestamp, timestamp_buffer);
}

void atlas_joint_packet_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_PACKET_SIZE],
    atlas_joint_packet_t* packet)
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* type_buffer = *buffer + ATLAS_JOINT_PACKET_TYPE_OFFSET;
    atlas_joint_packet_type_decode_binary(type_buffer, &packet->type);

    uint8_t* payload_buffer = *buffer + ATLAS_JOINT_PACKET_PAYLOAD_OFFSET;
    atlas_joint_packet_payload_decode_binary(payload_buffer,
                                             packet->type,
                                             &packet->payload);

    uint8_t* timestamp_buffer = *buffer + ATLAS_JOINT_PACKET_TIMESTAMP_OFFSET;
    atlas_joint_packet_timestamp_decode_binary(timestamp_buffer,
                                               &packet->timestamp);
}

void atlas_joint_packet_encode_binary_with_checksum(
    atlas_joint_packet_t const* packet,
    uint8_t (*buffer)[ATLAS_JOINT_PACKET_WITH_CHECKSUM_SIZE])
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* packet_buffer = *buffer;
    atlas_joint_packet_encode_binary(
        packet,
        (uint8_t (*)[ATLAS_JOINT_PACKET_SIZE])packet_buffer);

    atlas_joint_packet_checksum_t checksum;
    atlas_joint_packet_checksum_calculate(packet_buffer, &checksum);

    uint8_t* checksum_buffer = *buffer + ATLAS_JOINT_PACKET_CHECKSUM_OFFSET;
    atlas_joint_packet_checksum_encode_binary(&checksum, checksum_buffer);
}

void atlas_joint_packet_decode_binary_with_checksum(
    const uint8_t (*buffer)[ATLAS_JOINT_PACKET_WITH_CHECKSUM_SIZE],
    atlas_joint_packet_t* packet)
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* packet_buffer = *buffer;
    atlas_joint_packet_decode_binary(
        (const uint8_t (*)[ATLAS_JOINT_PACKET_SIZE])packet_buffer,
        packet);

    atlas_joint_packet_checksum_t calculated_checksum, received_checksum;
    atlas_joint_packet_checksum_calculate(packet_buffer, &calculated_checksum);

    uint8_t* checksum_buffer = *buffer + ATLAS_JOINT_PACKET_CHECKSUM_OFFSET;
    atlas_joint_packet_checksum_decode_binary(checksum_buffer,
                                              &received_checksum);

    if (received_checksum != calculated_checksum) {
        atlas_log("Joint packet checksum mismatch!\n\r");
    }
}

void atlas_robot_packet_print(atlas_robot_packet_t const* packet)
{
    ATLAS_ASSERT(packet != NULL);
}

void atlas_joint_packet_print(atlas_joint_packet_t const* packet)
{
    ATLAS_ASSERT(packet != NULL);
}

void atlas_robot_packet_dump(atlas_robot_packet_t const* packet)
{
    ATLAS_ASSERT(packet != NULL);

    atlas_log("Robot packet dump:\r\n");

    for (uint8_t* byte = (uint8_t*)packet;
         byte < (uint8_t*)packet + ATLAS_ROBOT_PACKET_SIZE;
         ++byte) {
        atlas_log("0x%02X ", *byte);
    }

    atlas_log("\r\n");
}

void atlas_joint_packet_dump(atlas_joint_packet_t const* packet)
{
    ATLAS_ASSERT(packet != NULL);

    atlas_log("Joint packet dump:\r\n");

    for (uint8_t* byte = (uint8_t*)packet;
         byte < (uint8_t*)packet + ATLAS_JOINT_PACKET_SIZE;
         ++byte) {
        atlas_log("0x%02X ", *byte);
    }

    atlas_log("\r\n");
}
