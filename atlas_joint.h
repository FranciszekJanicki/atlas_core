#ifndef ATLAS_CORE_ATLAS_JOINT_H
#define ATLAS_CORE_ATLAS_JOINT_H

#include "atlas_types.h"

typedef enum {
    ATLAS_JOINT_NUM_1,
    ATLAS_JOINT_NUM_2,
    ATLAS_JOINT_NUM_3,
    ATLAS_JOINT_NUM_4,
    ATLAS_JOINT_NUM_5,
    ATLAS_JOINT_NUM_6,
    ATLAS_JOINT_NUM,
} atlas_joint_num_t;

typedef struct {
    float32_t position;
} atlas_joint_data_t;

typedef struct {
} atlas_joint_start_t;

typedef struct {
} atlas_joint_stop_t;

typedef enum {
    ATLAS_JOINT_FAULT_ENCODER,
    ATLAS_JOINT_FAULT_DRIVER,
    ATLAS_JOINT_FAULT_CURRENT,
    ATLAS_JOINT_FAULT_NONE,
} atlas_joint_fault_t;

typedef struct {
} atlas_joint_ready_t;

typedef enum {
    ATLAS_JOINT_STATE_IDLE,
    ATLAS_JOINT_STATE_STARTED,
    ATLAS_JOINT_STATE_STOPPED,
    ATLAS_JOINT_STATE_INVALID,
} atlas_joint_state_t;

#endif // ATLAS_CORE_ATLAS_JOINT_H