#ifndef ATLAS_CORE_ATLAS_JOINT_H
#define ATLAS_CORE_ATLAS_JOINT_H

#include "atlas_types.h"
#include <stdint.h>

typedef enum {
    ATLAS_JOINT_NUM_1,
    ATLAS_JOINT_NUM_2,
    ATLAS_JOINT_NUM_3,
    ATLAS_JOINT_NUM_4,
    ATLAS_JOINT_NUM_5,
    ATLAS_JOINT_NUM_6,
    ATLAS_JOINT_NUM,
} atlas_joint_num_t;

#define ATLAS_JOINT_NUM_SIZE (sizeof(atlas_joint_num_t))

void atlas_joint_num_encode_binary(atlas_joint_num_t num,
                                   uint8_t (*buffer)[ATLAS_JOINT_NUM_SIZE]);

void atlas_joint_num_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_NUM_SIZE],
    atlas_joint_num_t* num);

void atlas_joint_num_encode_symbolic(atlas_joint_num_t num,
                                     char* buffer,
                                     size_t buffer_len);

void atlas_joint_num_decode_symbolic(char const* buffer,
                                     atlas_joint_num_t* num);

typedef enum {
    ATLAS_JOINT_STATE_READY,
    ATLAS_JOINT_STATE_RUNNING,
    ATLAS_JOINT_STATE_FAULT,
    ATLAS_JOINT_STATE_IDLE,
} atlas_joint_state_t;

#define ATLAS_JOINT_STATE_SIZE (sizeof(atlas_joint_state_t))

void atlas_joint_state_encode_binary(atlas_joint_state_t state,
                                     uint8_t (*buffer)[ATLAS_JOINT_STATE_SIZE]);

void atlas_joint_state_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_STATE_SIZE],
    atlas_joint_state_t* state);

void atlas_joint_state_encode_symbolic(atlas_joint_state_t state,
                                       char* buffer,
                                       size_t buffer_len);

void atlas_joint_state_decode_symbolic(char const* buffer,
                                       atlas_joint_state_t* state);

typedef struct {
    float32_t position;
    float32_t current;
} atlas_joint_measure_t;

#define ATLAS_JOINT_MEASURE_SIZE (sizeof(float32_t) + sizeof(float32_t))

void atlas_joint_measure_encode_binary(
    atlas_joint_measure_t const* measure,
    uint8_t (*buffer)[ATLAS_JOINT_MEASURE_SIZE]);

void atlas_joint_measure_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_MEASURE_SIZE],
    atlas_joint_measure_t* measure);

void atlas_joint_measure_encode_symbolic(atlas_joint_measure_t const* measure,
                                         char* buffer,
                                         size_t buffer_len);

void atlas_joint_measure_decode_symbolic(char const* buffer,
                                         atlas_joint_measure_t* measure);

typedef struct {
    float32_t position;
    float32_t delta_time;
} atlas_joint_reference_t;

#define ATLAS_JOINT_REFERENCE_SIZE (sizeof(float32_t) + sizeof(float32_t))

void atlas_joint_reference_encode_binary(
    atlas_joint_reference_t const* reference,
    uint8_t (*buffer)[ATLAS_JOINT_REFERENCE_SIZE]);

void atlas_joint_reference_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_REFERENCE_SIZE],
    atlas_joint_reference_t* reference);

void atlas_joint_reference_encode_symbolic(
    atlas_joint_reference_t const* reference,
    char* buffer,
    size_t buffer_len);

void atlas_joint_reference_decode_symbolic(char const* buffer,
                                           atlas_joint_reference_t* reference);

typedef struct {
    float32_t prop_gain;
    float32_t int_gain;
    float32_t dot_gain;
    float32_t sat_gain;
    float32_t dead_error;
    float32_t min_position;
    float32_t max_position;
    float32_t min_speed;
    float32_t max_speed;
    float32_t min_acceleration;
    float32_t max_acceleration;
    float32_t reset_position;
    float32_t step_change;
    int32_t microstep;
    float32_t current_limit;
    bool magnet_polarity;
} atlas_joint_parameters_t;

#define ATLAS_JOINT_PARAMETERS_SIZE \
    (sizeof(float32_t) * 14UL + sizeof(int32_t) + sizeof(bool))

void atlas_joint_parameters_encode_binary(
    atlas_joint_parameters_t const* parameters,
    uint8_t (*buffer)[ATLAS_JOINT_PARAMETERS_SIZE]);

void atlas_joint_parameters_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_PARAMETERS_SIZE],
    atlas_joint_parameters_t* parameters);

void atlas_joint_parameters_encode_symbolic(
    atlas_joint_parameters_t const* parameters,
    char* buffer,
    size_t buffer_len);

void atlas_joint_parameters_decode_symbolic(
    char const* buffer,
    atlas_joint_parameters_t* parameters);

bool atlas_joint_reference_is_equal(atlas_joint_reference_t const* reference1,
                                    atlas_joint_reference_t const* reference2);

bool atlas_joint_measure_is_equal(atlas_joint_measure_t const* measure1,
                                  atlas_joint_measure_t const* measure2);

typedef enum {
    ATLAS_JOINT_COMMAND_TYPE_GET_STATE,
    ATLAS_JOINT_COMMAND_TYPE_GET_MEASURE,
    ATLAS_JOINT_COMMAND_TYPE_SET_STATE,
    ATLAS_JOINT_COMMAND_TYPE_SET_REFERENCE,
    ATLAS_JOINT_COMMAND_TYPE_SET_PARAMETERS,
} atlas_joint_command_type_t;

#define ATLAS_JOINT_COMMAND_TYPE_OFFSET (0U)
#define ATLAS_JOINT_COMMAND_TYPE_SIZE (sizeof(atlas_joint_command_type_t))

typedef struct {
} atlas_joint_command_payload_get_state_t;

typedef struct {
} atlas_joint_command_payload_get_measure_t;

typedef struct {
    atlas_joint_state_t state;
} atlas_joint_command_payload_set_state_t;

typedef struct {
    atlas_joint_reference_t reference;
} atlas_joint_command_payload_set_reference_t;

typedef struct {
    atlas_joint_parameters_t parameters;
} atlas_joint_command_payload_set_parameters_t;

typedef union {
    atlas_joint_command_payload_get_state_t get_state;
    atlas_joint_command_payload_set_state_t set_state;
    atlas_joint_command_payload_set_reference_t set_reference;
    atlas_joint_command_payload_get_measure_t get_measure;
    atlas_joint_command_payload_set_parameters_t set_parameters;
} atlas_joint_command_payload_t;

#define ATLAS_JOINT_COMMAND_PAYLOAD_OFFSET \
    (ATLAS_JOINT_COMMAND_TYPE_OFFSET + ATLAS_JOINT_COMMAND_TYPE_SIZE)
#define ATLAS_JOINT_COMMAND_PAYLOAD_SIZE (sizeof(atlas_joint_command_payload_t))

typedef struct {
    atlas_joint_command_type_t type;
    atlas_joint_command_payload_t payload;
} atlas_joint_command_t;

#define ATLAS_JOINT_COMMAND_SIZE \
    (ATLAS_JOINT_COMMAND_TYPE_SIZE + ATLAS_JOINT_COMMAND_PAYLOAD_SIZE)

typedef enum {
    ATLAS_JOINT_RESPONSE_TYPE_GET_STATE,
    ATLAS_JOINT_RESPONSE_TYPE_GET_MEASURE,
    ATLAS_JOINT_RESPONSE_TYPE_SET_STATE,
    ATLAS_JOINT_RESPONSE_TYPE_SET_REFERENCE,
    ATLAS_JOINT_RESPONSE_TYPE_SET_PARAMETERS,
} atlas_joint_response_type_t;

#define ATLAS_JOINT_RESPONSE_TYPE_OFFSET (0U)
#define ATLAS_JOINT_RESPONSE_TYPE_SIZE (sizeof(atlas_joint_response_type_t))

typedef struct {
    atlas_joint_state_t state;
} atlas_joint_response_payload_get_state_t;

typedef struct {
    atlas_joint_measure_t measure;
} atlas_joint_response_payload_get_measure_t;

typedef struct {
    bool success;
} atlas_joint_response_payload_set_state_t;

typedef struct {
    bool success;
} atlas_joint_response_payload_set_reference_t;

typedef struct {
    bool success;
} atlas_joint_response_payload_set_parameters_t;

typedef union {
    atlas_joint_response_payload_get_state_t get_state;
    atlas_joint_response_payload_get_measure_t get_measure;
    atlas_joint_response_payload_set_state_t set_state;
    atlas_joint_response_payload_set_reference_t set_reference;
    atlas_joint_response_payload_set_parameters_t set_parameters;
} atlas_joint_response_payload_t;

#define ATLAS_JOINT_RESPONSE_PAYLOAD_OFFSET \
    (ATLAS_JOINT_RESPONSE_TYPE_OFFSET + ATLAS_JOINT_RESPONSE_TYPE_SIZE)
#define ATLAS_JOINT_RESPONSE_PAYLOAD_SIZE \
    (sizeof(atlas_joint_response_payload_t))

typedef struct {
    atlas_joint_response_type_t type;
    atlas_joint_response_payload_t payload;
} atlas_joint_response_t;

#define ATLAS_JOINT_RESPONSE_SIZE \
    (ATLAS_JOINT_RESPONSE_TYPE_SIZE + ATLAS_JOINT_RESPONSE_PAYLOAD_SIZE)

void atlas_joint_command_encode_binary(
    atlas_joint_command_t const* command,
    uint8_t (*buffer)[ATLAS_JOINT_COMMAND_SIZE]);

void atlas_joint_command_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_COMMAND_SIZE],
    atlas_joint_command_t* command);

void atlas_joint_response_encode_binary(
    atlas_joint_response_t const* response,
    uint8_t (*buffer)[ATLAS_JOINT_RESPONSE_SIZE]);

void atlas_joint_response_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_RESPONSE_SIZE],
    atlas_joint_response_t* response);

void atlas_joint_command_encode_symbolic(atlas_joint_command_t const* command,
                                         char* buffer,
                                         size_t buffer_len);

void atlas_joint_command_decode_symbolic(char const* buffer,
                                         atlas_joint_command_t* command);

void atlas_joint_response_encode_symbolic(
    atlas_joint_response_t const* response,
    char* buffer,
    size_t buffer_len);

void atlas_joint_response_decode_symbolic(char const* buffer,
                                          atlas_joint_response_t* response);

#endif // ATLAS_CORE_ATLAS_JOINT_H
