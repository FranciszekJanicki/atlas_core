#ifndef ATLAS_CORE_ATLAS_CONFIG_H
#define ATLAS_CORE_ATLAS_CONFIG_H

#include "atlas_data.h"
#include "atlas_joint_num.h"
#include <stdint.h>

typedef enum {
    ATLAS_CONFIG_TYPE_ROB,
    ATLAS_CONFIG_TYPE_HMI,
} atlas_config_type_t;

typedef struct {
    float32_t prop_gain, int_gain, dot_gain, sat_gain;
    float32_t min_speed, max_speed, min_position, max_position;
    float32_t step_change;
    float32_t current_limit;
} atlas_joint_config_t;

typedef struct {
    atlas_joint_config_t joint_configs[ATLAS_JOINT_NUM];
    float32_t joints_delta_time;
} atlas_joints_config_t;

typedef int atlas_kinematics_config_t;

typedef struct {
    atlas_joints_config_t joints_config;
    atlas_kinematics_config_t kinematics_config;
} atlas_rob_config_t;

typedef atlas_rob_config_t atlas_config_payload_rob_t;

typedef int atlas_ui_config_t;

typedef int atlas_sd_config_t;

typedef struct {
    atlas_ui_config_t ui_config;
    atlas_sd_config_t sd_config;
} atlas_hmi_config_t;

typedef atlas_hmi_config_t atlas_config_payload_hmi_t;

typedef union {
    atlas_config_payload_rob_t rob;
    atlas_config_payload_hmi_t hmi;
} atlas_config_payload_t;

typedef struct {
    atlas_config_type_t type;
    atlas_config_payload_t payload;
} atlas_config_t;

#endif // ATLAS_CORE_ATLAS_CONFIG_H