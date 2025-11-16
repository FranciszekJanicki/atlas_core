#include "atlas_joint.h"
#include "atlas_utility.h"
#include "utility.h"
#include <string.h>

void atlas_joint_num_encode_binary(atlas_joint_num_t num,
                                   uint8_t (*buffer)[ATLAS_JOINT_NUM_SIZE])
{
    ATLAS_ASSERT(buffer != NULL);

    uint8x4_t num_buffer = uint32_to_uint8x4_be(num);
    memcpy(*buffer, num_buffer.data, 4UL);
}

void atlas_joint_num_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_NUM_SIZE],
    atlas_joint_num_t* num)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(num != NULL);

    uint8x4_t num_buffer;
    memcpy(num_buffer.data, *buffer, 4UL);
    *num = uint8x4_be_to_uint32(num_buffer);
}

void atlas_joint_num_encode_symbolic(atlas_joint_num_t num,
                                     char* buffer,
                                     size_t buffer_len)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(buffer_len > 0UL);

    int written_len = snprintf(buffer, buffer_len, "NUM: %d", num);
    buffer[written_len] = '\0';
}

void atlas_joint_num_decode_symbolic(char const* buffer, atlas_joint_num_t* num)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(strlen(buffer) > 0UL);
    ATLAS_ASSERT(num != NULL);

    sscanf(buffer, "NUM: %d", &num);
}

void atlas_joint_state_encode_binary(atlas_joint_state_t state,
                                     uint8_t (*buffer)[ATLAS_JOINT_STATE_SIZE])
{
    ATLAS_ASSERT(buffer != NULL);

    uint8x4_t state_buffer = uint32_to_uint8x4_be(state);
    memcpy(*buffer, state_buffer.data, 4UL);
}

void atlas_joint_state_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_STATE_SIZE],
    atlas_joint_state_t* state)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(state != NULL);

    uint8x4_t state_buffer;
    memcpy(state_buffer.data, *buffer, 4UL);
    *state = uint8x4_be_to_uint32(state_buffer);
}

void atlas_joint_state_encode_symbolic(atlas_joint_state_t state,
                                       char* buffer,
                                       size_t buffer_len)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(buffer_len > 0UL);

    int written_len = snprintf(buffer, buffer_len, "STATE: %d", state);
    buffer[written_len] = '\0';
}

void atlas_joint_state_decode_symbolic(char const* buffer,
                                       atlas_joint_state_t* state)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(strlen(buffer) > 0UL);
    ATLAS_ASSERT(state != NULL);

    sscanf(buffer, "STATE: %d", state);
}

void atlas_joint_measure_encode_binary(
    atlas_joint_measure_t const* measure,
    uint8_t (*buffer)[ATLAS_JOINT_MEASURE_SIZE])
{
    ATLAS_ASSERT(measure != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8x4_t position_buffer = float32_to_uint8x4_be(measure->position);
    memcpy(*buffer, position_buffer.data, 4UL);

    uint8x4_t current_buffer = float32_to_uint8x4_be(measure->current);
    memcpy(*buffer + 4UL, current_buffer.data, 4UL);
}

void atlas_joint_measure_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_MEASURE_SIZE],
    atlas_joint_measure_t* measure)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(measure != NULL);

    uint8x4_t position_buffer;
    memcpy(position_buffer.data, *buffer, 4UL);
    measure->position = uint8x4_be_to_uint32(position_buffer);

    uint8x4_t current_buffer;
    memcpy(current_buffer.data, *buffer + 4UL, 4UL);
    measure->current = uint8x4_be_to_uint32(current_buffer);
}

void atlas_joint_measure_encode_symbolic(atlas_joint_measure_t const* measure,
                                         char* buffer,
                                         size_t buffer_len)
{
    ATLAS_ASSERT(measure != NULL);
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(buffer_len > 0UL);

    int written_len = snprintf(buffer,
                               buffer_len,
                               "MEASURE POSITION: %f, CURRENT: %f",
                               measure->position,
                               measure->current);
    buffer[written_len] = '\0';
}

void atlas_joint_measure_decode_symbolic(char const* buffer,
                                         atlas_joint_measure_t* measure)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(strlen(buffer) > 0UL);
    ATLAS_ASSERT(measure != NULL);

    sscanf(buffer,
           "MEASURE POSITION: %f, CURRENT: %f",
           &measure->position,
           &measure->current);
}

void atlas_joint_reference_encode_binary(
    atlas_joint_reference_t const* reference,
    uint8_t (*buffer)[ATLAS_JOINT_REFERENCE_SIZE])
{
    ATLAS_ASSERT(reference != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8x4_t position_buffer = float32_to_uint8x4_be(reference->position);
    memcpy(*buffer, position_buffer.data, 4UL);

    uint8x4_t delta_time_buffer = float32_to_uint8x4_be(reference->delta_time);
    memcpy(*buffer + 4UL, delta_time_buffer.data, 4UL);
}

void atlas_joint_reference_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_REFERENCE_SIZE],
    atlas_joint_reference_t* reference)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(reference != NULL);

    uint8x4_t position_buffer;
    memcpy(position_buffer.data, *buffer, 4UL);
    reference->position = uint8x4_be_to_uint32(position_buffer);

    uint8x4_t delta_time_buffer;
    memcpy(delta_time_buffer.data, *buffer + 4UL, 4UL);
    reference->delta_time = uint8x4_be_to_uint32(delta_time_buffer);
}

void atlas_joint_reference_encode_symbolic(
    atlas_joint_reference_t const* reference,
    char* buffer,
    size_t buffer_len)
{
    ATLAS_ASSERT(reference != NULL);
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(buffer_len > 0UL);

    int written_len = snprintf(buffer,
                               buffer_len,
                               "REFERENCE POSITION: %f, DELTA_TIME: %f",
                               reference->position,
                               reference->delta_time);
    buffer[written_len] = '\0';
}

void atlas_joint_reference_decode_symbolic(char const* buffer,
                                           atlas_joint_reference_t* reference)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(strlen(buffer) > 0UL);
    ATLAS_ASSERT(reference != NULL);

    sscanf(buffer,
           "REFERENCE POSITION: %f, DELTA_TIME: %f",
           &reference->position,
           &reference->delta_time);
}

void atlas_joint_parameters_encode_binary(
    atlas_joint_parameters_t const* parameters,
    uint8_t (*buffer)[ATLAS_JOINT_PARAMETERS_SIZE])
{
    ATLAS_ASSERT(parameters != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8x4_t prop_gain_buffer = float32_to_uint8x4_be(parameters->prop_gain);
    memcpy(*buffer, prop_gain_buffer.data, 4UL);

    uint8x4_t int_gain_buffer = float32_to_uint8x4_be(parameters->int_gain);
    memcpy(*buffer + 4UL, int_gain_buffer.data, 4UL);

    uint8x4_t dot_gain_buffer = float32_to_uint8x4_be(parameters->dot_gain);
    memcpy(*buffer + 8UL, dot_gain_buffer.data, 4UL);

    uint8x4_t sat_gain_buffer = float32_to_uint8x4_be(parameters->sat_gain);
    memcpy(*buffer + 12UL, sat_gain_buffer.data, 4UL);

    uint8x4_t dead_error_buffer = float32_to_uint8x4_be(parameters->dead_error);
    memcpy(*buffer + 16UL, dead_error_buffer.data, 4UL);

    uint8x4_t min_position_buffer =
        float32_to_uint8x4_be(parameters->min_position);
    memcpy(*buffer + 20UL, min_position_buffer.data, 4UL);

    uint8x4_t max_position_buffer =
        float32_to_uint8x4_be(parameters->max_position);
    memcpy(*buffer + 24UL, max_position_buffer.data, 4UL);

    uint8x4_t min_speed_buffer = float32_to_uint8x4_be(parameters->min_speed);
    memcpy(*buffer + 28UL, min_speed_buffer.data, 4UL);

    uint8x4_t max_speed_buffer = float32_to_uint8x4_be(parameters->max_speed);
    memcpy(*buffer + 32UL, max_speed_buffer.data, 4UL);

    uint8x4_t min_acceleration_buffer =
        float32_to_uint8x4_be(parameters->min_acceleration);
    memcpy(*buffer + 36UL, min_acceleration_buffer.data, 4UL);

    uint8x4_t max_acceleration_buffer =
        float32_to_uint8x4_be(parameters->max_acceleration);
    memcpy(*buffer + 40UL, max_acceleration_buffer.data, 4UL);

    uint8x4_t reset_position_buffer =
        float32_to_uint8x4_be(parameters->reset_position);
    memcpy(*buffer + 44UL, reset_position_buffer.data, 4UL);

    uint8x4_t step_change_buffer =
        float32_to_uint8x4_be(parameters->step_change);
    memcpy(*buffer + 48UL, step_change_buffer.data, 4UL);

    uint8x4_t microstep_buffer = float32_to_uint8x4_be(parameters->microstep);
    memcpy(*buffer + 52UL, microstep_buffer.data, 4UL);

    uint8x4_t current_limit_buffer =
        float32_to_uint8x4_be(parameters->current_limit);
    memcpy(*buffer + 56UL, current_limit_buffer.data, 4UL);

    memcpy(*buffer + 60UL, &parameters->magnet_polarity, 1UL);
}

void atlas_joint_parameters_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_PARAMETERS_SIZE],
    atlas_joint_parameters_t* parameters)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(parameters != NULL);

    uint8x4_t prop_gain_buffer;
    memcpy(prop_gain_buffer.data, *buffer, 4UL);
    parameters->prop_gain = uint8x4_be_to_float32(prop_gain_buffer);

    uint8x4_t int_gain_buffer;
    memcpy(int_gain_buffer.data, *buffer + 4UL, 4UL);
    parameters->int_gain = uint8x4_be_to_float32(int_gain_buffer);

    uint8x4_t dot_gain_buffer;
    memcpy(dot_gain_buffer.data, *buffer + 8UL, 4UL);
    parameters->dot_gain = uint8x4_be_to_float32(dot_gain_buffer);

    uint8x4_t sat_gain_buffer;
    memcpy(sat_gain_buffer.data, *buffer + 12UL, 4UL);
    parameters->sat_gain = uint8x4_be_to_float32(sat_gain_buffer);

    uint8x4_t dead_error_buffer;
    memcpy(dead_error_buffer.data, *buffer + 16UL, 4UL);
    parameters->dead_error = uint8x4_be_to_float32(dead_error_buffer);

    uint8x4_t min_position_buffer;
    memcpy(min_position_buffer.data, *buffer + 20UL, 4UL);
    parameters->min_position = uint8x4_be_to_float32(min_position_buffer);

    uint8x4_t max_position_buffer;
    memcpy(max_position_buffer.data, *buffer + 24UL, 4UL);
    parameters->max_position = uint8x4_be_to_float32(max_position_buffer);

    uint8x4_t min_speed_buffer;
    memcpy(min_speed_buffer.data, *buffer + 28UL, 4UL);
    parameters->min_speed = uint8x4_be_to_float32(min_speed_buffer);

    uint8x4_t max_speed_buffer;
    memcpy(max_speed_buffer.data, *buffer + 32UL, 4UL);
    parameters->max_speed = uint8x4_be_to_float32(max_speed_buffer);

    uint8x4_t min_acceleration_buffer;
    memcpy(min_acceleration_buffer.data, *buffer + 36UL, 4UL);
    parameters->min_acceleration =
        uint8x4_be_to_float32(min_acceleration_buffer);

    uint8x4_t max_acceleration_buffer;
    memcpy(max_acceleration_buffer.data, *buffer + 40UL, 4UL);
    parameters->max_acceleration =
        uint8x4_be_to_float32(max_acceleration_buffer);

    uint8x4_t reset_position_buffer;
    memcpy(reset_position_buffer.data, *buffer + 44UL, 4UL);
    parameters->reset_position = uint8x4_be_to_float32(reset_position_buffer);

    uint8x4_t step_change_buffer;
    memcpy(step_change_buffer.data, *buffer + 48UL, 4UL);
    parameters->step_change = uint8x4_be_to_float32(step_change_buffer);

    uint8x4_t microstep_buffer;
    memcpy(microstep_buffer.data, *buffer + 52UL, 4UL);
    parameters->microstep = uint8x4_be_to_float32(microstep_buffer);

    uint8x4_t current_limit_buffer;
    memcpy(current_limit_buffer.data, *buffer + 56UL, 4UL);
    parameters->current_limit = uint8x4_be_to_float32(current_limit_buffer);

    memcpy(&parameters->magnet_polarity, *buffer + 60UL, 1UL);
}

void atlas_joint_parameters_encode_symbolic(
    atlas_joint_parameters_t const* parameters,
    char* buffer,
    size_t buffer_len)
{
    ATLAS_ASSERT(parameters != NULL);
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(buffer_len > 0UL);

    int written_len = snprintf(
        buffer,
        buffer_len,
        "PARAMETERS PROP_GAIN: %f, INT_GAIN: %f, DOT_GAIN: %f, SAT_GAIN: %f, "
        "DEAD_ERROR: %f, MIN_POSITION: %f, MAX_POSITION: %f, MIN_SPEED: %f, "
        "MAX_SPEED: %f, MIN_ACCELERATION: %f, MAX_ACCELERATION: %f, "
        "RESET_POSITION: %f, STEP_CHANGE: %f, MICROSTEP: %d, CURRENT_LIMIT: "
        "%f, MAGNET_POLARITY: %d",
        parameters->prop_gain,
        parameters->int_gain,
        parameters->dot_gain,
        parameters->sat_gain,
        parameters->dead_error,
        parameters->min_position,
        parameters->max_position,
        parameters->min_speed,
        parameters->max_speed,
        parameters->min_acceleration,
        parameters->max_acceleration,
        parameters->reset_position,
        parameters->step_change,
        parameters->microstep,
        parameters->current_limit,
        parameters->magnet_polarity);
    buffer[written_len] = '\0';
}

void atlas_joint_parameters_decode_symbolic(
    char const* buffer,
    atlas_joint_parameters_t* parameters)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(strlen(buffer) > 0UL);
    ATLAS_ASSERT(parameters != NULL);

    sscanf(
        buffer,
        "PARAMETERS PROP_GAIN: %f, INT_GAIN: %f, DOT_GAIN: %f, SAT_GAIN: %f, "
        "DEAD_ERROR: %f, MIN_POSITION: %f, MAX_POSITION: %f, MIN_SPEED: %f, "
        "MAX_SPEED: %f, MIN_ACCELERATION: %f, MAX_ACCELERATION: %f, "
        "RESET_POSITION: %f, STEP_CHANGE: %f, MICROSTEP: %d, CURRENT_LIMIT: "
        "%f, MAGNET_POLARITY: %d",
        &parameters->prop_gain,
        &parameters->int_gain,
        &parameters->dot_gain,
        &parameters->sat_gain,
        &parameters->dead_error,
        &parameters->min_position,
        &parameters->max_position,
        &parameters->min_speed,
        &parameters->max_speed,
        &parameters->min_acceleration,
        &parameters->max_acceleration,
        &parameters->reset_position,
        &parameters->step_change,
        &parameters->microstep,
        &parameters->current_limit,
        &parameters->magnet_polarity);
}

bool atlas_joint_reference_is_equal(atlas_joint_reference_t const* reference1,
                                    atlas_joint_reference_t const* reference2)
{
    ATLAS_ASSERT(reference1 != NULL);
    ATLAS_ASSERT(reference2 != NULL);

    return reference1->delta_time == reference2->delta_time &&
           reference2->position == reference2->position;
}

bool atlas_joint_measure_is_equal(atlas_joint_measure_t const* measure1,
                                  atlas_joint_measure_t const* measure2)
{
    ATLAS_ASSERT(measure1 != NULL);
    ATLAS_ASSERT(measure2 != NULL);

    return measure1->current == measure1->current &&
           measure1->position == measure2->position;
}

static inline void atlas_joint_command_type_encode_binary(
    atlas_joint_command_type_t type,
    uint8_t* buffer)
{
    uint8x4_t type_buffer = uint32_to_uint8x4_be(type);
    memcpy(buffer, type_buffer.data, 4UL);
}

static inline void atlas_joint_command_payload_get_state_encode_binary(
    atlas_joint_command_payload_get_state_t const* get_state,
    uint8_t* buffer)
{}

static inline void atlas_joint_command_payload_get_measure_encode_binary(
    atlas_joint_command_payload_get_measure_t const* get_measure,
    uint8_t* buffer)
{}

static inline void atlas_joint_command_payload_set_reference_encode_binary(
    atlas_joint_command_payload_set_reference_t const* set_reference,
    uint8_t* buffer)
{
    atlas_joint_reference_encode_binary(
        &set_reference->reference,
        (uint8_t (*)[ATLAS_JOINT_REFERENCE_SIZE])buffer);
}

static inline void atlas_joint_command_payload_set_state_encode_binary(
    atlas_joint_command_payload_set_state_t const* set_state,
    uint8_t* buffer)
{
    atlas_joint_state_encode_binary(
        set_state->state,
        (uint8_t (*)[ATLAS_JOINT_STATE_SIZE])buffer);
}

static inline void atlas_joint_command_payload_set_parameters_encode_binary(
    atlas_joint_command_payload_set_parameters_t const* set_parameters,
    uint8_t* buffer)
{
    atlas_joint_parameters_encode_binary(
        &set_parameters->parameters,
        (uint8_t (*)[ATLAS_JOINT_PARAMETERS_SIZE])buffer);
}

static inline void atlas_joint_command_payload_encode_binary(
    atlas_joint_command_type_t type,
    atlas_joint_command_payload_t const* payload,
    uint8_t* buffer)
{
    switch (type) {
        case ATLAS_JOINT_COMMAND_TYPE_GET_STATE: {
            atlas_joint_command_payload_get_state_encode_binary(
                &payload->get_state,
                buffer);
        } break;
        case ATLAS_JOINT_COMMAND_TYPE_GET_MEASURE: {
            atlas_joint_command_payload_get_measure_encode_binary(
                &payload->get_measure,
                buffer);
        } break;
        case ATLAS_JOINT_COMMAND_TYPE_SET_STATE: {
            atlas_joint_command_payload_set_state_encode_binary(
                &payload->set_state,
                buffer);
        } break;
        case ATLAS_JOINT_COMMAND_TYPE_SET_REFERENCE: {
            atlas_joint_command_payload_set_reference_encode_binary(
                &payload->set_reference,
                buffer);
        } break;
        case ATLAS_JOINT_COMMAND_TYPE_SET_PARAMETERS: {
            atlas_joint_command_payload_set_parameters_encode_binary(
                &payload->set_parameters,
                buffer);
        } break;
        default: {
        } break;
    }
}

void atlas_joint_command_encode_binary(
    atlas_joint_command_t const* command,
    uint8_t (*buffer)[ATLAS_JOINT_COMMAND_SIZE])
{
    ATLAS_ASSERT(command != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* type_buffer = *buffer + ATLAS_JOINT_COMMAND_TYPE_OFFSET;
    atlas_joint_command_type_encode_binary(command->type, type_buffer);

    uint8_t* payload_buffer = *buffer + ATLAS_JOINT_COMMAND_PAYLOAD_OFFSET;
    atlas_joint_command_payload_encode_binary(command->type,
                                              &command->payload,
                                              payload_buffer);
}

static inline void atlas_joint_command_type_decode_binary(
    uint8_t const* buffer,
    atlas_joint_command_type_t* type)
{
    uint8x4_t type_buffer;
    memcpy(type_buffer.data, buffer, 4UL);
    *type = uint8x4_be_to_uint32(type_buffer);
}

static inline void atlas_joint_command_payload_get_state_decode_binary(
    uint8_t const* buffer,
    atlas_joint_command_payload_get_state_t* get_state)
{}

static inline void atlas_joint_command_payload_get_measure_decode_binary(
    uint8_t const* buffer,
    atlas_joint_command_payload_get_measure_t* get_measure)
{}

static inline void atlas_joint_command_payload_set_state_decode_binary(
    uint8_t const* buffer,
    atlas_joint_command_payload_set_state_t* set_state)
{
    atlas_joint_state_decode_binary(
        (const uint8_t (*)[ATLAS_JOINT_STATE_SIZE])buffer,
        &set_state->state);
}

static inline void atlas_joint_command_payload_set_reference_decode_binary(
    uint8_t const* buffer,
    atlas_joint_command_payload_set_reference_t* set_reference)
{
    atlas_joint_reference_decode_binary(
        (const uint8_t (*)[ATLAS_JOINT_REFERENCE_SIZE])buffer,
        &set_reference->reference);
}

static inline void atlas_joint_command_payload_set_parameters_decode_binary(
    uint8_t const* buffer,
    atlas_joint_command_payload_set_parameters_t* set_parameters)
{
    atlas_joint_parameters_decode_binary(
        (const uint8_t (*)[ATLAS_JOINT_PARAMETERS_SIZE])buffer,
        &set_parameters->parameters);
}

static inline void atlas_joint_command_payload_decode_binary(
    uint8_t const* buffer,
    atlas_joint_command_type_t type,
    atlas_joint_command_payload_t* payload)
{
    switch (type) {
        case ATLAS_JOINT_COMMAND_TYPE_GET_STATE: {
            atlas_joint_command_payload_get_state_decode_binary(
                buffer,
                &payload->get_state);
        } break;
        case ATLAS_JOINT_COMMAND_TYPE_GET_MEASURE: {
            atlas_joint_command_payload_get_measure_decode_binary(
                buffer,
                &payload->get_measure);
        } break;
        case ATLAS_JOINT_COMMAND_TYPE_SET_STATE: {
            atlas_joint_command_payload_set_state_decode_binary(
                buffer,
                &payload->set_state);
        } break;
        case ATLAS_JOINT_COMMAND_TYPE_SET_REFERENCE: {
            atlas_joint_command_payload_set_reference_decode_binary(
                buffer,
                &payload->set_reference);
        } break;
        case ATLAS_JOINT_COMMAND_TYPE_SET_PARAMETERS: {
            atlas_joint_command_payload_set_parameters_decode_binary(
                buffer,
                &payload->set_parameters);
        } break;
        default: {
        } break;
    }
}

void atlas_joint_command_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_COMMAND_SIZE],
    atlas_joint_command_t* command)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(command != NULL);

    uint8_t const* type_buffer = *buffer + ATLAS_JOINT_COMMAND_TYPE_OFFSET;
    atlas_joint_command_type_decode_binary(type_buffer, &command->type);

    uint8_t const* payload_buffer =
        *buffer + ATLAS_JOINT_COMMAND_PAYLOAD_OFFSET;
    atlas_joint_command_payload_decode_binary(type_buffer,
                                              command->type,
                                              &command->payload);
}

static inline void atlas_joint_response_result_encode_binary(
    atlas_joint_response_result_t result,
    uint8_t* buffer)
{
    uint8x4_t result_buffer = uint32_to_uint8x4_be(result);
    memcpy(buffer, result_buffer.data, 4UL);
}

static inline void atlas_joint_response_type_encode_binary(
    atlas_joint_response_type_t type,
    uint8_t* buffer)
{
    uint8x4_t type_buffer = uint32_to_uint8x4_be(type);
    memcpy(buffer, type_buffer.data, 4UL);
}

static inline void atlas_joint_response_payload_get_state_encode_binary(
    atlas_joint_response_payload_get_state_t const* get_state,
    uint8_t* buffer)
{
    atlas_joint_state_encode_binary(
        get_state->state,
        (uint8_t (*)[ATLAS_JOINT_STATE_SIZE])buffer);
}

static inline void atlas_joint_response_payload_get_measure_encode_binary(
    atlas_joint_response_payload_get_measure_t const* get_measure,
    uint8_t* buffer)
{
    atlas_joint_measure_encode_binary(
        &get_measure->measure,
        (uint8_t (*)[ATLAS_JOINT_MEASURE_SIZE])buffer);
}

static inline void atlas_joint_response_payload_set_state_encode_binary(
    atlas_joint_response_payload_set_state_t const* set_state,
    uint8_t* buffer)
{}

static inline void atlas_joint_response_payload_set_reference_encode_binary(
    atlas_joint_response_payload_set_reference_t const* set_reference,
    uint8_t* buffer)
{}

static inline void atlas_joint_response_payload_set_parameters_encode_binary(
    atlas_joint_response_payload_set_parameters_t const* set_parameters,
    uint8_t* buffer)
{}

static inline void atlas_joint_response_payload_encode_binary(
    atlas_joint_response_type_t type,
    atlas_joint_response_payload_t const* payload,
    uint8_t* buffer)
{
    switch (type) {
        case ATLAS_JOINT_RESPONSE_TYPE_GET_STATE: {
            atlas_joint_response_payload_get_state_encode_binary(
                &payload->get_state,
                buffer);
        } break;
        case ATLAS_JOINT_RESPONSE_TYPE_GET_MEASURE: {
            atlas_joint_response_payload_get_measure_encode_binary(
                &payload->get_measure,
                buffer);
        } break;
        case ATLAS_JOINT_RESPONSE_TYPE_SET_STATE: {
            atlas_joint_response_payload_set_state_encode_binary(
                &payload->set_state,
                buffer);
        } break;
        case ATLAS_JOINT_RESPONSE_TYPE_SET_REFERENCE: {
            atlas_joint_response_payload_set_reference_encode_binary(
                &payload->set_reference,
                buffer);
        } break;
        case ATLAS_JOINT_RESPONSE_TYPE_SET_PARAMETERS: {
            atlas_joint_response_payload_set_parameters_encode_binary(
                &payload->set_parameters,
                buffer);
        } break;
        default: {
        } break;
    }
}

void atlas_joint_response_encode_binary(
    atlas_joint_response_t const* response,
    uint8_t (*buffer)[ATLAS_JOINT_RESPONSE_SIZE])
{
    ATLAS_ASSERT(response != NULL);
    ATLAS_ASSERT(buffer != NULL);

    uint8_t* result_buffer = *buffer + ATLAS_JOINT_RESPONSE_RESULT_OFFSET;
    atlas_joint_response_result_encode_binary(response->result, result_buffer);

    uint8_t* type_buffer = *buffer + ATLAS_JOINT_RESPONSE_TYPE_OFFSET;
    atlas_joint_response_type_encode_binary(response->type, type_buffer);

    uint8_t* payload_buffer = *buffer + ATLAS_JOINT_RESPONSE_PAYLOAD_OFFSET;
    atlas_joint_response_payload_encode_binary(response->type,
                                               &response->payload,
                                               payload_buffer);
}

static inline void atlas_joint_response_result_decode_binary(
    uint8_t const* buffer,
    atlas_joint_response_result_t* result)
{
    uint8x4_t result_buffer;
    memcpy(buffer, result_buffer.data, 4UL);
    *result = uint8x4_be_to_uint32(result_buffer);
}

static inline void atlas_joint_response_type_decode_binary(
    uint8_t const* buffer,
    atlas_joint_response_type_t* type)
{
    uint8x4_t type_buffer;
    memcpy(buffer, type_buffer.data, 4UL);
    *type = uint8x4_be_to_uint32(type_buffer);
}

static inline void atlas_joint_response_payload_get_state_decode_binary(
    uint8_t const* buffer,
    atlas_joint_response_payload_get_state_t* get_state)
{
    atlas_joint_state_decode_binary(
        (const uint8_t (*)[ATLAS_JOINT_STATE_SIZE])buffer,
        &get_state->state);
}

static inline void atlas_joint_response_payload_get_measure_decode_binary(
    uint8_t const* buffer,
    atlas_joint_response_payload_get_measure_t* get_measure)
{
    atlas_joint_measure_decode_binary(
        (const uint8_t (*)[ATLAS_JOINT_MEASURE_SIZE])buffer,
        &get_measure->measure);
}

static inline void atlas_joint_response_payload_set_state_decode_binary(
    uint8_t const* buffer,
    atlas_joint_response_payload_set_state_t* set_state)
{}

static inline void atlas_joint_response_payload_set_reference_decode_binary(
    uint8_t const* buffer,
    atlas_joint_response_payload_set_reference_t* set_reference)
{}

static inline void atlas_joint_response_payload_set_parameters_decode_binary(
    uint8_t const* buffer,
    atlas_joint_response_payload_set_parameters_t* set_parameters)
{}

static inline void atlas_joint_response_payload_decode_binary(
    uint8_t const* buffer,
    atlas_joint_response_type_t type,
    atlas_joint_response_payload_t* payload)
{
    switch (type) {
        case ATLAS_JOINT_RESPONSE_TYPE_GET_STATE: {
            atlas_joint_response_payload_get_state_decode_binary(
                buffer,
                &payload->get_state);
        } break;
        case ATLAS_JOINT_RESPONSE_TYPE_GET_MEASURE: {
            atlas_joint_response_payload_get_measure_decode_binary(
                buffer,
                &payload->get_measure);
        } break;
        case ATLAS_JOINT_RESPONSE_TYPE_SET_STATE: {
            atlas_joint_response_payload_set_state_decode_binary(
                buffer,
                &payload->set_state);
        } break;
        case ATLAS_JOINT_RESPONSE_TYPE_SET_REFERENCE: {
            atlas_joint_response_payload_set_reference_decode_binary(
                buffer,
                &payload->set_reference);
        } break;
        case ATLAS_JOINT_RESPONSE_TYPE_SET_PARAMETERS: {
            atlas_joint_response_payload_set_parameters_decode_binary(
                buffer,
                &payload->set_parameters);
        } break;
        default: {
        } break;
    }
}

void atlas_joint_response_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_RESPONSE_SIZE],
    atlas_joint_response_t* response)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(response != NULL);

    uint8_t const* result_buffer = *buffer + ATLAS_JOINT_RESPONSE_RESULT_OFFSET;
    atlas_joint_response_result_decode_binary(result_buffer, &response->result);

    uint8_t const* type_buffer = *buffer + ATLAS_JOINT_RESPONSE_TYPE_OFFSET;
    atlas_joint_response_type_decode_binary(type_buffer, &response->type);

    uint8_t const* payload_buffer =
        *buffer + ATLAS_JOINT_RESPONSE_PAYLOAD_OFFSET;
    atlas_joint_response_payload_decode_binary(payload_buffer,
                                               response->type,
                                               &response->payload);
}

/* TODO */
void atlas_joint_command_encode_symbolic(atlas_joint_command_t const* command,
                                         char* buffer,
                                         size_t buffer_len)
{
    ATLAS_ASSERT(command != NULL);
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(buffer_len > 0UL);
}

void atlas_joint_command_decode_symbolic(char const* buffer,
                                         atlas_joint_command_t* command)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(strlen(buffer) >= 0UL);
    ATLAS_ASSERT(command != NULL);
}

void atlas_joint_response_encode_symbolic(
    atlas_joint_response_t const* response,
    char* buffer,
    size_t buffer_len)
{
    ATLAS_ASSERT(response != NULL);
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(buffer_len > 0UL);
}

void atlas_joint_response_decode_symbolic(char const* buffer,
                                          atlas_joint_response_t* response)
{
    ATLAS_ASSERT(buffer != NULL);
    ATLAS_ASSERT(strlen(buffer) >= 0UL);
    ATLAS_ASSERT(response != NULL);
}

/* END TODO */
