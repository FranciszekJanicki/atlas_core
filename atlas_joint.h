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

typedef enum {
    ATLAS_JOINT_STATE_IDLE,
    ATLAS_JOINT_STATE_READY,
    ATLAS_JOINT_STATE_RUNNING,
    ATLAS_JOINT_STATE_FAULT,
} atlas_joint_state_t;

typedef struct {
} atlas_joint_start_t;

typedef struct {
} atlas_joint_stop_t;

typedef struct {
} atlas_joint_reset_t;

typedef struct {
} atlas_joint_ready_t;

typedef struct {
} atlas_joint_fault_t;

typedef struct {
    float32_t position;
    float32_t current;
} atlas_joint_measure_t;

typedef struct {
    float32_t position;
    float32_t delta_time;
} atlas_joint_reference_t;

bool atlas_joint_reference_is_equal(atlas_joint_reference_t const* reference1,
                                    atlas_joint_reference_t const* reference2);

void atlas_joint_reference_print(atlas_joint_reference_t const* reference);

bool atlas_joint_measure_is_equal(atlas_joint_measure_t const* measure1,
                                  atlas_joint_measure_t const* measure2);

void atlas_joint_measure_print(atlas_joint_measure_t const* measure);


#endif // ATLAS_CORE_ATLAS_JOINT_H