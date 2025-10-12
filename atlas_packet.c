#include "atlas_packet.h"
#include "atlas_utility.h"
#include "string.h"
#include "utility.h"

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

static inline void atlas_robot_packet_payload_joint_ready_encode(
    atlas_robot_packet_payload_joint_ready_t const* joint_ready,
    uint8_t* buffer)
{}

static inline void atlas_robot_packet_payload_joint_started_encode(
    atlas_robot_packet_payload_joint_started_t const* joint_started,
    uint8_t* buffer)
{}

static inline void atlas_robot_packet_payload_joint_stopped_encode(
    atlas_robot_packet_payload_joint_stopped_t const* joint_stopped,
    uint8_t* buffer)
{}

static inline void atlas_robot_packet_payload_joint_fault_encode(
    atlas_robot_packet_payload_joint_fault_t const* joint_fault,
    uint8_t* buffer)
{
    buffer[0] = joint_fault->message[0];
    buffer[1] = joint_fault->message[1];
    buffer[2] = joint_fault->message[2];
    buffer[3] = joint_fault->message[3];
    buffer[4] = joint_fault->message[4];
    buffer[5] = joint_fault->message[5];
    buffer[6] = joint_fault->message[6];
    buffer[7] = joint_fault->message[7];
    buffer[8] = joint_fault->message[8];
    buffer[9] = joint_fault->message[9];
}

static inline void atlas_robot_packet_payload_joint_measure_encode(
    atlas_robot_packet_payload_joint_measure_t const* joint_measure,
    uint8_t* buffer)
{
    uint8x4_t position_buffer = float32_to_uint8x4_be(joint_measure->position);
    buffer[0] = position_buffer.data[0];
    buffer[1] = position_buffer.data[1];
    buffer[2] = position_buffer.data[2];
    buffer[3] = position_buffer.data[3];
}

static inline void atlas_robot_packet_payload_encode(
    atlas_robot_packet_type_t type,
    atlas_robot_packet_payload_t const* payload,
    uint8_t* buffer)
{
    switch (type) {
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_READY: {
            atlas_robot_packet_payload_joint_ready_encode(&payload->joint_ready,
                                                          buffer);
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_STARTED: {
            atlas_robot_packet_payload_joint_started_encode(
                &payload->joint_started,
                buffer);
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_STOPPED: {
            atlas_robot_packet_payload_joint_stopped_encode(
                &payload->joint_stopped,
                buffer);
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT: {
            atlas_robot_packet_payload_joint_fault_encode(&payload->joint_fault,
                                                          buffer);
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_MEASURE: {
            atlas_robot_packet_payload_joint_measure_encode(
                &payload->joint_measure,
                buffer);
        } break;
        default: {
        } break;
    }
}

static inline void atlas_robot_packet_payload_joint_ready_decode(
    uint8_t const* buffer,
    atlas_robot_packet_payload_joint_ready_t* joint_ready)
{}

static inline void atlas_robot_packet_payload_joint_started_decode(
    uint8_t const* buffer,
    atlas_robot_packet_payload_joint_started_t* joint_started)
{}

static inline void atlas_robot_packet_payload_joint_stopped_decode(
    uint8_t const* buffer,
    atlas_robot_packet_payload_joint_stopped_t* joint_stopped)
{}

static inline void atlas_robot_packet_payload_joint_fault_decode(
    uint8_t const* buffer,
    atlas_robot_packet_payload_joint_fault_t* joint_fault)
{
    joint_fault->message[0] = buffer[0];
    joint_fault->message[1] = buffer[1];
    joint_fault->message[2] = buffer[2];
    joint_fault->message[3] = buffer[3];
    joint_fault->message[4] = buffer[4];
    joint_fault->message[5] = buffer[5];
    joint_fault->message[6] = buffer[6];
    joint_fault->message[7] = buffer[7];
    joint_fault->message[8] = buffer[8];
    joint_fault->message[9] = buffer[9];
}

static inline void atlas_robot_packet_payload_joint_measure_decode(
    uint8_t const* buffer,
    atlas_robot_packet_payload_joint_measure_t* joint_measure)
{
    uint8x4_t position_buffer;
    position_buffer.data[0] = buffer[0];
    position_buffer.data[1] = buffer[1];
    position_buffer.data[2] = buffer[2];
    position_buffer.data[3] = buffer[3];
    joint_measure->position = uint8x4_be_to_float32(position_buffer);

    uint8x4_t current_buffer;
    current_buffer.data[0] = buffer[4];
    current_buffer.data[1] = buffer[5];
    current_buffer.data[2] = buffer[6];
    current_buffer.data[3] = buffer[7];
    joint_measure->current = uint8x4_be_to_float32(current_buffer);
}

static inline void atlas_robot_packet_payload_decode(
    uint8_t const* buffer,
    atlas_robot_packet_type_t type,
    atlas_robot_packet_payload_t* payload)
{
    switch (type) {
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_READY: {
            atlas_robot_packet_payload_joint_ready_decode(
                buffer,
                &payload->joint_ready);
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_STARTED: {
            atlas_robot_packet_payload_joint_started_decode(
                buffer,
                &payload->joint_started);
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_STOPPED: {
            atlas_robot_packet_payload_joint_stopped_decode(
                buffer,
                &payload->joint_stopped);
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT: {
            atlas_robot_packet_payload_joint_fault_decode(
                buffer,
                &payload->joint_fault);
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_MEASURE: {
            atlas_robot_packet_payload_joint_measure_decode(
                buffer,
                &payload->joint_measure);
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

    uint8_t* type_buffer = *buffer + ATLAS_ROBOT_PACKET_TYPE_OFFSET;
    atlas_robot_packet_type_encode(packet->type, type_buffer);

    uint8_t* origin_buffer = *buffer + ATLAS_ROBOT_PACKET_ORIGIN_OFFSET;
    atlas_robot_packet_origin_encode(packet->origin, origin_buffer);

    uint8_t* payload_buffer = *buffer + ATLAS_ROBOT_PACKET_PAYLOAD_OFFSET;
    atlas_robot_packet_payload_encode(packet->type,
                                      &packet->payload,
                                      payload_buffer);

    uint8_t* timestamp_buffer = *buffer + ATLAS_ROBOT_PACKET_TIMESTAMP_OFFSET;
    atlas_robot_packet_timestamp_encode(&packet->timestamp, timestamp_buffer);
}

void atlas_robot_packet_decode(const uint8_t (*buffer)[ATLAS_ROBOT_PACKET_SIZE],
                               atlas_robot_packet_t* packet)
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* type_buffer = *buffer + ATLAS_ROBOT_PACKET_TYPE_OFFSET;
    atlas_robot_packet_type_decode(type_buffer, &packet->type);

    uint8_t* origin_buffer = *buffer + ATLAS_ROBOT_PACKET_ORIGIN_OFFSET;
    atlas_robot_packet_origin_decode(origin_buffer, &packet->origin);

    uint8_t* payload_buffer = *buffer + ATLAS_ROBOT_PACKET_PAYLOAD_OFFSET;
    atlas_robot_packet_payload_decode(payload_buffer,
                                      packet->type,
                                      &packet->payload);

    uint8_t* timestamp_buffer = *buffer + ATLAS_ROBOT_PACKET_TIMESTAMP_OFFSET;
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

static inline void atlas_joint_packet_payload_joint_start_encode(
    atlas_joint_packet_payload_joint_start_t const* joint_start,
    uint8_t* buffer)
{}

static inline void atlas_joint_packet_payload_joint_stop_encode(
    atlas_joint_packet_payload_joint_stop_t const* joint_stop,
    uint8_t* buffer)
{}

static inline void atlas_joint_packet_payload_joint_reference_encode(
    atlas_joint_packet_payload_joint_reference_t const* joint_reference,
    uint8_t* buffer)
{
    uint8x4_t position_buffer =
        float32_to_uint8x4_be(joint_reference->position);
    buffer[0] = position_buffer.data[0];
    buffer[1] = position_buffer.data[1];
    buffer[2] = position_buffer.data[2];
    buffer[3] = position_buffer.data[3];

    uint8x4_t delta_time_buffer =
        float32_to_uint8x4_be(joint_reference->delta_time);
    buffer[4] = delta_time_buffer.data[0];
    buffer[5] = delta_time_buffer.data[1];
    buffer[6] = delta_time_buffer.data[2];
    buffer[7] = delta_time_buffer.data[3];
}

static inline void atlas_joint_packet_payload_encode(
    atlas_joint_packet_type_t type,
    atlas_joint_packet_payload_t const* payload,
    uint8_t* buffer)
{
    switch (type) {
        case ATLAS_JOINT_PACKET_TYPE_JOINT_START: {
            atlas_joint_packet_payload_joint_start_encode(&payload->joint_start,
                                                          buffer);
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_STOP: {
            atlas_joint_packet_payload_joint_stop_encode(&payload->joint_stop,
                                                         buffer);
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_REFERENCE: {
            atlas_joint_packet_payload_joint_reference_encode(
                &payload->joint_reference,
                buffer);
        } break;
        default: {
        } break;
    }
}

static inline void atlas_joint_packet_payload_joint_start_decode(
    uint8_t const* buffer,
    atlas_joint_packet_payload_joint_start_t* joint_start)
{}

static inline void atlas_joint_packet_payload_joint_stop_decode(
    uint8_t const* buffer,
    atlas_joint_packet_payload_joint_stop_t* joint_stop)
{}

static inline void atlas_joint_packet_payload_joint_reference_decode(
    uint8_t const* buffer,
    atlas_joint_packet_payload_joint_reference_t* joint_reference)
{
    uint8x4_t position_buffer;
    position_buffer.data[0] = buffer[0];
    position_buffer.data[1] = buffer[1];
    position_buffer.data[2] = buffer[2];
    position_buffer.data[3] = buffer[3];
    joint_reference->position = uint8x4_be_to_float32(position_buffer);

    uint8x4_t delta_time_buffer;
    delta_time_buffer.data[0] = buffer[4];
    delta_time_buffer.data[1] = buffer[5];
    delta_time_buffer.data[2] = buffer[6];
    delta_time_buffer.data[3] = buffer[7];
    joint_reference->delta_time = uint8x4_be_to_float32(delta_time_buffer);
}

static inline void atlas_joint_packet_payload_decode(
    uint8_t const* buffer,
    atlas_joint_packet_type_t type,
    atlas_joint_packet_payload_t* payload)
{
    switch (type) {
        case ATLAS_JOINT_PACKET_TYPE_JOINT_START: {
            atlas_joint_packet_payload_joint_start_decode(
                buffer,
                &payload->joint_start);
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_STOP: {
            atlas_joint_packet_payload_joint_stop_decode(buffer,
                                                         &payload->joint_stop);
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_REFERENCE: {
            atlas_joint_packet_payload_joint_reference_decode(
                buffer,
                &payload->joint_reference);
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

    uint8_t* checksum_buffer = *buffer + ATLAS_ROBOT_PACKET_CHECKSUM_OFFSET;
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

    uint8_t* checksum_buffer = *buffer + ATLAS_ROBOT_PACKET_CHECKSUM_OFFSET;
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

    uint8_t* type_buffer = *buffer + ATLAS_JOINT_PACKET_TYPE_OFFSET;
    atlas_joint_packet_type_encode(packet->type, type_buffer);

    uint8_t* payload_buffer = *buffer + ATLAS_JOINT_PACKET_PAYLOAD_OFFSET;
    atlas_joint_packet_payload_encode(packet->type,
                                      &packet->payload,
                                      payload_buffer);

    uint8_t* timestamp_buffer = *buffer + ATLAS_JOINT_PACKET_TIMESTAMP_OFFSET;
    atlas_joint_packet_timestamp_encode(&packet->timestamp, timestamp_buffer);
}

void atlas_joint_packet_decode(const uint8_t (*buffer)[ATLAS_JOINT_PACKET_SIZE],
                               atlas_joint_packet_t* packet)
{
    ATLAS_ASSERT(packet != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* type_buffer = *buffer + ATLAS_JOINT_PACKET_TYPE_OFFSET;
    atlas_joint_packet_type_decode(type_buffer, &packet->type);

    uint8_t* payload_buffer = *buffer + ATLAS_JOINT_PACKET_PAYLOAD_OFFSET;
    atlas_joint_packet_payload_decode(payload_buffer,
                                      packet->type,
                                      &packet->payload);

    uint8_t* timestamp_buffer = *buffer + ATLAS_JOINT_PACKET_TIMESTAMP_OFFSET;
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

    uint8_t* checksum_buffer = *buffer + ATLAS_JOINT_PACKET_CHECKSUM_OFFSET;
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

    uint8_t* checksum_buffer = *buffer + ATLAS_JOINT_PACKET_CHECKSUM_OFFSET;
    atlas_joint_packet_checksum_decode(checksum_buffer, &received_checksum);

    if (received_checksum != calculated_checksum) {
        atlas_log("Joint packet checksum mismatch!\n\r");
    }
}

static inline void atlas_robot_packet_type_print(atlas_robot_packet_type_t type)
{
    switch (type) {
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_STARTED: {
            atlas_log("Robot packet type: JOINT_STARTED\n\r");
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_STOPPED: {
            atlas_log("Robot packet type: JOINT_STOPPED\n\r");
        } break;
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
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_STARTED: {
            atlas_log("Robot packet payload: <empty>\n\r");
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_STOPPED: {
            atlas_log("Robot packet payload: <empty>\n\r");
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_READY: {
            atlas_log("Robot packet payload: <empty>\n\r");
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT: {
            atlas_log("Robot packet payload: %s\n\r",
                      payload->joint_fault.message);
        } break;
        case ATLAS_ROBOT_PACKET_TYPE_JOINT_MEASURE: {
            atlas_log("Robot packet payload: position %f, current %f\n\r",
                      payload->joint_measure.position,
                      payload->joint_measure.current);
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
        case ATLAS_JOINT_PACKET_TYPE_JOINT_START: {
            atlas_log("Joint packet payload: <empty>\n\r");
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_STOP: {
            atlas_log("Joint packet payload: <empty>\n\r");
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_REFERENCE: {
            atlas_log("Joint packet payload: position %f, delta_time %f\n\r",
                      payload->joint_reference.position,
                      payload->joint_reference.delta_time);
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
