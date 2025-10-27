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
    strncpy((char*)buffer, joint_fault->message, sizeof(joint_fault->message));
    buffer[sizeof(joint_fault->message) - 1] = '\0';
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
    strncpy(joint_fault->message,
            (char const*)buffer,
            sizeof(joint_fault->message));
    joint_fault->message[sizeof(joint_fault->message) - 1] = '\0';
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

static inline void atlas_joint_packet_payload_joint_reset_encode(
    atlas_joint_packet_payload_joint_reset_t const* joint_reset,
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

static inline void atlas_joint_packet_payload_joint_parameters_encode(
    atlas_joint_packet_payload_joint_parameters_t const* joint_parameters,
    uint8_t* buffer)
{
    uint8x4_t prop_gain_buffer =
        float32_to_uint8x4_be(joint_parameters->prop_gain);
    buffer[0] = prop_gain_buffer.data[0];
    buffer[1] = prop_gain_buffer.data[1];
    buffer[2] = prop_gain_buffer.data[2];
    buffer[3] = prop_gain_buffer.data[3];

    uint8x4_t int_gain_buffer =
        float32_to_uint8x4_be(joint_parameters->int_gain);
    buffer[4] = int_gain_buffer.data[0];
    buffer[5] = int_gain_buffer.data[1];
    buffer[6] = int_gain_buffer.data[2];
    buffer[7] = int_gain_buffer.data[3];

    uint8x4_t dot_gain_buffer =
        float32_to_uint8x4_be(joint_parameters->dot_gain);
    buffer[8] = dot_gain_buffer.data[0];
    buffer[9] = dot_gain_buffer.data[1];
    buffer[10] = dot_gain_buffer.data[2];
    buffer[11] = dot_gain_buffer.data[3];

    uint8x4_t sat_gain_buffer =
        float32_to_uint8x4_be(joint_parameters->sat_gain);
    buffer[12] = sat_gain_buffer.data[0];
    buffer[13] = sat_gain_buffer.data[1];
    buffer[14] = sat_gain_buffer.data[2];
    buffer[15] = sat_gain_buffer.data[3];

    uint8x4_t dead_error_buffer =
        float32_to_uint8x4_be(joint_parameters->dead_error);
    buffer[16] = dead_error_buffer.data[0];
    buffer[17] = dead_error_buffer.data[1];
    buffer[18] = dead_error_buffer.data[2];
    buffer[19] = dead_error_buffer.data[3];

    uint8x4_t min_speed_buffer =
        float32_to_uint8x4_be(joint_parameters->min_speed);
    buffer[20] = min_speed_buffer.data[0];
    buffer[21] = min_speed_buffer.data[1];
    buffer[22] = min_speed_buffer.data[2];
    buffer[23] = min_speed_buffer.data[3];

    uint8x4_t max_speed_buffer =
        float32_to_uint8x4_be(joint_parameters->max_speed);
    buffer[24] = max_speed_buffer.data[0];
    buffer[25] = max_speed_buffer.data[1];
    buffer[26] = max_speed_buffer.data[2];
    buffer[27] = max_speed_buffer.data[3];

    uint8x4_t home_position_buffer =
        float32_to_uint8x4_be(joint_parameters->home_position);
    buffer[28] = home_position_buffer.data[0];
    buffer[29] = home_position_buffer.data[1];
    buffer[30] = home_position_buffer.data[2];
    buffer[31] = home_position_buffer.data[3];

    uint8x4_t min_position_buffer =
        float32_to_uint8x4_be(joint_parameters->min_position);
    buffer[32] = min_position_buffer.data[0];
    buffer[33] = min_position_buffer.data[1];
    buffer[34] = min_position_buffer.data[2];
    buffer[35] = min_position_buffer.data[3];

    uint8x4_t max_position_buffer =
        float32_to_uint8x4_be(joint_parameters->max_position);
    buffer[36] = max_position_buffer.data[0];
    buffer[37] = max_position_buffer.data[1];
    buffer[38] = max_position_buffer.data[2];
    buffer[39] = max_position_buffer.data[3];

    uint8x4_t min_acceleration_buffer =
        float32_to_uint8x4_be(joint_parameters->min_acceleration);
    buffer[40] = min_acceleration_buffer.data[0];
    buffer[41] = min_acceleration_buffer.data[1];
    buffer[42] = min_acceleration_buffer.data[2];
    buffer[43] = min_acceleration_buffer.data[3];

    uint8x4_t max_acceleration_buffer =
        float32_to_uint8x4_be(joint_parameters->max_acceleration);
    buffer[44] = max_acceleration_buffer.data[0];
    buffer[45] = max_acceleration_buffer.data[1];
    buffer[46] = max_acceleration_buffer.data[2];
    buffer[47] = max_acceleration_buffer.data[3];

    uint8x4_t step_change_buffer =
        float32_to_uint8x4_be(joint_parameters->step_change);
    buffer[48] = step_change_buffer.data[0];
    buffer[49] = step_change_buffer.data[1];
    buffer[50] = step_change_buffer.data[2];
    buffer[51] = step_change_buffer.data[3];

    uint8x4_t current_limit_buffer =
        float32_to_uint8x4_be(joint_parameters->current_limit);
    buffer[52] = current_limit_buffer.data[0];
    buffer[53] = current_limit_buffer.data[1];
    buffer[54] = current_limit_buffer.data[2];
    buffer[55] = current_limit_buffer.data[3];

    buffer[56] = joint_parameters->magnet_polarity;
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
        case ATLAS_JOINT_PACKET_TYPE_JOINT_RESET: {
            atlas_joint_packet_payload_joint_reset_encode(&payload->joint_reset,
                                                          buffer);
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_REFERENCE: {
            atlas_joint_packet_payload_joint_reference_encode(
                &payload->joint_reference,
                buffer);
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_PARAMETERS: {
            atlas_joint_packet_payload_joint_parameters_encode(
                &payload->joint_parameters,
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

static inline void atlas_joint_packet_payload_joint_reset_decode(
    uint8_t const* buffer,
    atlas_joint_packet_payload_joint_reset_t* joint_reset)
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

static inline void atlas_joint_packet_payload_joint_parameters_decode(
    uint8_t const* buffer,
    atlas_joint_packet_payload_joint_parameters_t* joint_parameters)
{
    uint8x4_t prop_gain_buffer;
    prop_gain_buffer.data[0] = buffer[0];
    prop_gain_buffer.data[1] = buffer[1];
    prop_gain_buffer.data[2] = buffer[2];
    prop_gain_buffer.data[3] = buffer[3];
    joint_parameters->prop_gain = uint8x4_be_to_float32(prop_gain_buffer);

    uint8x4_t int_gain_buffer;
    int_gain_buffer.data[0] = buffer[4];
    int_gain_buffer.data[1] = buffer[5];
    int_gain_buffer.data[2] = buffer[6];
    int_gain_buffer.data[3] = buffer[7];
    joint_parameters->int_gain = uint8x4_be_to_float32(int_gain_buffer);

    uint8x4_t dot_gain_buffer;
    dot_gain_buffer.data[0] = buffer[8];
    dot_gain_buffer.data[1] = buffer[9];
    dot_gain_buffer.data[2] = buffer[10];
    dot_gain_buffer.data[3] = buffer[11];
    joint_parameters->dot_gain = uint8x4_be_to_float32(dot_gain_buffer);

    uint8x4_t sat_gain_buffer;
    sat_gain_buffer.data[0] = buffer[12];
    sat_gain_buffer.data[1] = buffer[13];
    sat_gain_buffer.data[2] = buffer[14];
    sat_gain_buffer.data[3] = buffer[15];
    joint_parameters->sat_gain = uint8x4_be_to_float32(sat_gain_buffer);

    uint8x4_t dead_error_buffer;
    dead_error_buffer.data[0] = buffer[16];
    dead_error_buffer.data[1] = buffer[17];
    dead_error_buffer.data[2] = buffer[18];
    dead_error_buffer.data[3] = buffer[19];
    joint_parameters->dead_error = uint8x4_be_to_float32(dead_error_buffer);

    uint8x4_t min_speed_buffer;
    min_speed_buffer.data[0] = buffer[20];
    min_speed_buffer.data[1] = buffer[21];
    min_speed_buffer.data[2] = buffer[22];
    min_speed_buffer.data[3] = buffer[23];
    joint_parameters->min_speed = uint8x4_be_to_float32(min_speed_buffer);

    uint8x4_t max_speed_buffer;
    max_speed_buffer.data[0] = buffer[24];
    max_speed_buffer.data[1] = buffer[25];
    max_speed_buffer.data[2] = buffer[26];
    max_speed_buffer.data[3] = buffer[27];
    joint_parameters->max_speed = uint8x4_be_to_float32(max_speed_buffer);

    uint8x4_t home_position_buffer;
    home_position_buffer.data[0] = buffer[28];
    home_position_buffer.data[1] = buffer[29];
    home_position_buffer.data[2] = buffer[30];
    home_position_buffer.data[3] = buffer[31];
    joint_parameters->home_position =
        uint8x4_be_to_float32(home_position_buffer);

    uint8x4_t min_position_buffer;
    min_position_buffer.data[0] = buffer[32];
    min_position_buffer.data[1] = buffer[33];
    min_position_buffer.data[2] = buffer[34];
    min_position_buffer.data[3] = buffer[35];
    joint_parameters->min_position = uint8x4_be_to_float32(min_position_buffer);

    uint8x4_t max_position_buffer;
    max_position_buffer.data[0] = buffer[36];
    max_position_buffer.data[1] = buffer[37];
    max_position_buffer.data[2] = buffer[38];
    max_position_buffer.data[3] = buffer[39];
    joint_parameters->max_position = uint8x4_be_to_float32(max_position_buffer);

    uint8x4_t min_acceleration_buffer;
    min_acceleration_buffer.data[0] = buffer[40];
    min_acceleration_buffer.data[1] = buffer[41];
    min_acceleration_buffer.data[2] = buffer[42];
    min_acceleration_buffer.data[3] = buffer[43];
    joint_parameters->min_acceleration =
        uint8x4_be_to_float32(min_acceleration_buffer);

    uint8x4_t max_acceleration_buffer;
    max_acceleration_buffer.data[0] = buffer[44];
    max_acceleration_buffer.data[1] = buffer[45];
    max_acceleration_buffer.data[2] = buffer[46];
    max_acceleration_buffer.data[3] = buffer[47];
    joint_parameters->max_acceleration =
        uint8x4_be_to_float32(max_acceleration_buffer);

    uint8x4_t step_change_buffer;
    step_change_buffer.data[0] = buffer[48];
    step_change_buffer.data[1] = buffer[49];
    step_change_buffer.data[2] = buffer[50];
    step_change_buffer.data[3] = buffer[51];
    joint_parameters->step_change = uint8x4_be_to_float32(step_change_buffer);

    uint8x4_t current_limit_buffer;
    current_limit_buffer.data[0] = buffer[52];
    current_limit_buffer.data[1] = buffer[53];
    current_limit_buffer.data[2] = buffer[54];
    current_limit_buffer.data[3] = buffer[55];
    joint_parameters->current_limit =
        uint8x4_be_to_float32(current_limit_buffer);

    joint_parameters->magnet_polarity = buffer[56];
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
        case ATLAS_JOINT_PACKET_TYPE_JOINT_RESET: {
            atlas_joint_packet_payload_joint_reset_decode(
                buffer,
                &payload->joint_reset);
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_REFERENCE: {
            atlas_joint_packet_payload_joint_reference_decode(
                buffer,
                &payload->joint_reference);
        } break;
        case ATLAS_JOINT_PACKET_TYPE_JOINT_PARAMETERS: {
            atlas_joint_packet_payload_joint_parameters_decode(
                buffer,
                &payload->joint_parameters);
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
