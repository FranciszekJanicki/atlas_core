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
    switch (type) {
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_MEASURE: {
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

        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT: {
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_READY: {
        } break;
        default: {
        } break;
    }
}

static inline void atlas_robot_packet_payload_decode(
    uint8_t const* buffer,
    atlas_robot_packet_type_t type,
    atlas_robot_packet_payload_t* payload)
{
    switch (type) {
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_MEASURE: {
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

            payload->joint_measure.current =
                uint8x4_be_to_float32(current_buffer);

        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT: {
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_READY: {
        } break;
        default: {
        } break;
    }
}

static inline void atlas_robot_packet_timestamp_encode(
    atlas_robot_packet_timestamp_t const* timestamp,
    uint8_t* buffer)
{
    atlas_timestamp_encode(timestamp,
                           (uint8_t (*)[ATLAS_TIMESTAMP_SIZE])buffer);
}

static inline void atlas_robot_packet_timestamp_decode(
    uint8_t const* buffer,
    atlas_robot_packet_timestamp_t* timestamp)
{
    atlas_timestamp_decode((const uint8_t (*)[ATLAS_TIMESTAMP_SIZE])buffer,
                           timestamp);
}

static inline void atlas_robot_packet_checksum_encode(
    atlas_robot_packet_checksum_t const* checksum,
    uint8_t* buffer)
{
    atlas_checksum_encode(checksum, (uint8_t (*)[ATLAS_CHECKSUM_SIZE])buffer);
}

static inline void atlas_robot_packet_checksum_decode(
    uint8_t const* buffer,
    atlas_robot_packet_checksum_t* checksum)
{
    atlas_checksum_decode((const uint8_t (*)[ATLAS_CHECKSUM_SIZE])buffer,
                          checksum);
}

static inline void atlas_robot_packet_checksum_calculate(
    uint8_t const* buffer,
    atlas_robot_packet_checksum_t* checksum)
{
    atlas_checksum_encode(checksum, (uint8_t (*)[ATLAS_CHECKSUM_SIZE])buffer);
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
    atlas_robot_packet_timestamp_encode(&packet->timestamp, timestamp_buffer);
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
    atlas_robot_packet_timestamp_decode(timestamp_buffer, &packet->timestamp);
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
    switch (type) {
        case ATLAS_JOINT_PACKET_TYPE_JOINT_REFERENCE: {
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
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_START: {
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_STOP: {
        } break;
        default: {
        } break;
    }
}

static inline void atlas_joint_packet_payload_decode(
    uint8_t const* buffer,
    atlas_joint_packet_type_t type,
    atlas_joint_packet_payload_t* payload)
{
    switch (type) {
        case ATLAS_JOINT_PACKET_TYPE_JOINT_REFERENCE: {
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
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_START: {
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_STOP: {
        } break;
        default: {
        } break;
    }
}

static inline void atlas_joint_packet_timestamp_encode(
    atlas_joint_packet_timestamp_t const* timestamp,
    uint8_t* buffer)
{
    atlas_timestamp_encode(timestamp,
                           (uint8_t (*)[ATLAS_TIMESTAMP_SIZE])buffer);
}

static inline void atlas_joint_packet_timestamp_decode(
    uint8_t const* buffer,
    atlas_joint_packet_timestamp_t* timestamp)
{
    atlas_timestamp_decode((const uint8_t (*)[ATLAS_TIMESTAMP_SIZE])buffer,
                           timestamp);
}

static inline void atlas_joint_packet_checksum_encode(
    atlas_joint_packet_checksum_t const* checksum,
    uint8_t* buffer)
{
    atlas_checksum_encode(checksum, (uint8_t (*)[ATLAS_CHECKSUM_SIZE])buffer);
}

static inline void atlas_joint_packet_checksum_decode(
    uint8_t const* buffer,
    atlas_joint_packet_checksum_t* checksum)
{
    atlas_checksum_decode((const uint8_t (*)[ATLAS_CHECKSUM_SIZE])buffer,
                          checksum);
}

static inline void atlas_joint_packet_checksum_calculate(
    uint8_t const* buffer,
    atlas_joint_packet_checksum_t* checksum)
{
    atlas_checksum_encode(checksum, (uint8_t (*)[ATLAS_CHECKSUM_SIZE])buffer);
}

void atlas_robot_packet_encode_with_checksum(
    atlas_robot_packet_t const* packet,
    uint8_t (*buffer)[ATLAS_ROBOT_PACKET_WITH_CHECKSUM_SIZE])
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* packet_buffer = *buffer;
    atlas_robot_packet_encode(
        packet,
        (uint8_t (*)[ATLAS_ROBOT_PACKET_SIZE])packet_buffer);

    atlas_robot_packet_checksum_t checksum;
    atlas_robot_packet_checksum_calculate(packet_buffer, &checksum);

    uint8_t* checksum_buffer = packet_buffer + sizeof(atlas_robot_packet_t);
    atlas_robot_packet_checksum_encode(&checksum, checksum_buffer);
}

void atlas_robot_packet_decode_with_checksum(
    const uint8_t (*buffer)[ATLAS_ROBOT_PACKET_WITH_CHECKSUM_SIZE],
    atlas_robot_packet_t* packet)
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* packet_buffer = *buffer;
    atlas_robot_packet_decode(
        (const uint8_t (*)[ATLAS_ROBOT_PACKET_SIZE])packet_buffer,
        packet);

    atlas_robot_packet_checksum_t calculated_checksum, received_checksum;
    atlas_robot_packet_checksum_calculate(packet_buffer, &calculated_checksum);

    uint8_t* checksum_buffer = packet_buffer + sizeof(atlas_robot_packet_t);
    atlas_robot_packet_checksum_decode(checksum_buffer, &received_checksum);

    if (received_checksum != calculated_checksum) {
        atlas_log("Robot packet checksum mismatch!\n\r");
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
    atlas_joint_packet_timestamp_encode(&packet->timestamp, timestamp_buffer);
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
    atlas_joint_packet_timestamp_decode(timestamp_buffer, &packet->timestamp);
}

void atlas_joint_packet_encode_with_checksum(
    atlas_joint_packet_t const* packet,
    uint8_t (*buffer)[ATLAS_JOINT_PACKET_WITH_CHECKSUM_SIZE])
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* packet_buffer = *buffer;
    atlas_joint_packet_encode(
        packet,
        (uint8_t (*)[ATLAS_JOINT_PACKET_SIZE])packet_buffer);

    atlas_joint_packet_checksum_t checksum;
    atlas_joint_packet_checksum_calculate(packet_buffer, &checksum);

    uint8_t* checksum_buffer = packet_buffer + sizeof(atlas_joint_packet_t);
    atlas_joint_packet_checksum_encode(&checksum, checksum_buffer);
}

void atlas_joint_packet_decode_with_checksum(
    const uint8_t (*buffer)[ATLAS_JOINT_PACKET_WITH_CHECKSUM_SIZE],
    atlas_joint_packet_t* packet)
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* packet_buffer = *buffer;
    atlas_joint_packet_decode(
        (const uint8_t (*)[ATLAS_JOINT_PACKET_SIZE])packet_buffer,
        packet);

    atlas_joint_packet_checksum_t calculated_checksum, received_checksum;
    atlas_joint_packet_checksum_calculate(packet_buffer, &calculated_checksum);

    uint8_t* checksum_buffer = packet_buffer + sizeof(atlas_joint_packet_t);
    atlas_joint_packet_checksum_decode(checksum_buffer, &received_checksum);

    if (received_checksum != calculated_checksum) {
        atlas_log("Joint packet checksum mismatch!\n\r");
    }
}

static inline void atlas_robot_packet_type_print(atlas_robot_packet_type_t type)
{
    switch (type) {
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_READY: {
            atlas_log("Robot packet type: JOINT_READY\n\r");
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT: {
            atlas_log("Robot packet type: JOINT_FAULT\n\r");
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_MEASURE: {
            atlas_log("Robot packet type: JOINT_MEASURE\n\r");
        } break;
        default: {
            atlas_log("Robot packet type: UNKNOWN\n\r");
        } break;
    }
}

static void atlas_robot_packet_origin_print(atlas_robot_packet_origin_t origin)
{
    atlas_log("Robot packet origin: JOINT %d\n\r", origin + 1);
}

static void atlas_robot_packet_payload_print(
    atlas_robot_packet_type_t type,
    atlas_robot_packet_payload_t const* payload)
{
    switch (type) {
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_MEASURE: {
            atlas_log("Robot packet payload: position %f, current %f\n\r",
                      payload->joint_measure.position,
                      payload->joint_measure.current);
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT: {
            atlas_log("Robot packet payload: <empty>\n\r");
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_READY: {
            atlas_log("Robot packet payload: <empty>\n\r");
        } break;
        default: {
            atlas_log("Robot packet payload: UNKNOWN\n\r");
        } break;
    }
}

static inline void atlas_robot_packet_timestamp_print(
    atlas_robot_packet_timestamp_t const* timestamp)
{
    atlas_timestamp_print(timestamp);
}

static inline void atlas_robot_packet_checksum_print(
    atlas_robot_packet_checksum_t const* checksum)
{
    atlas_checksum_print(checksum);
}

void atlas_robot_packet_print(atlas_robot_packet_t const* packet)
{
    ATLAS_ASSERT(packet != NULL);

    atlas_robot_packet_type_print(packet->type);
    atlas_robot_packet_origin_print(packet->origin);
    atlas_robot_packet_payload_print(packet->type, &packet->payload);
    atlas_robot_packet_timestamp_print(&packet->timestamp);
}

static inline void atlas_joint_packet_type_print(atlas_joint_packet_type_t type)
{
    switch (type) {
        case ATLAS_JOINT_PACKET_TYPE_JOINT_START: {
            atlas_log("Joint packet type: JOINT_START\n\r");
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_STOP: {
            atlas_log("Joint packet type: JOINT_STOP\n\r");
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_RESET: {
            atlas_log("Joint packet type: JOINT_RESET\n\r");
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_REFERENCE: {
            atlas_log("Joint packet type: JOINT_REFERENCE\n\r");
        } break;
        default: {
            atlas_log("Joint packet type: UNKNOWN\n\r");
        } break;
    }
}

static inline void atlas_joint_packet_payload_print(
    atlas_joint_packet_type_t type,
    atlas_joint_packet_payload_t const* payload)
{
    switch (type) {
        case ATLAS_JOINT_PACKET_TYPE_JOINT_REFERENCE: {
            atlas_log("Joint packet payload: position %f, delta_time %f\n\r",
                      payload->joint_reference.position,
                      payload->joint_reference.delta_time);
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_START: {
            atlas_log("Joint packet payload: <empty>\n\r");
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_STOP: {
            atlas_log("Joint packet payload: <empty>\n\r");
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_RESET: {
            atlas_log("Joint packet payload: <empty>\n\r");
        } break;
        default: {
            atlas_log("Joint packet payload: UNKNOWN\n\r");
        } break;
    }
}

static inline void atlas_joint_packet_timestamp_print(
    atlas_joint_packet_timestamp_t const* timestamp)
{
    atlas_timestamp_print(timestamp);
}

static inline void atlas_joint_packet_checksum_print(
    atlas_joint_packet_checksum_t const* checksum)
{
    atlas_checksum_print(checksum);
}

void atlas_joint_packet_print(atlas_joint_packet_t const* packet)
{
    ATLAS_ASSERT(packet != NULL);

    atlas_joint_packet_type_print(packet->type);
    atlas_joint_packet_payload_print(packet->type, &packet->payload);
    atlas_joint_packet_timestamp_print(&packet->timestamp);
}