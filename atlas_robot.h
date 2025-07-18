#ifndef ATLAS_CORE_ATLAS_ROBOT_H
#define ATLAS_CORE_ATLAS_ROBOT_H

#include "atlas_data.h"

typedef enum {
    ATLAS_ROBOT_DATA_TYPE_JOINTS,
    ATLAS_ROBOT_DATA_TYPE_CARTESIAN,
} atlas_robot_data_type_t;

typedef atlas_joints_data_t atlas_robot_data_payload_joints_t;
typedef atlas_cartesian_data_t atlas_robot_data_payload_cartesian_t;

typedef union {
    atlas_robot_data_payload_joints_t joints;
    atlas_robot_data_payload_cartesian_t cartesian;
} atlas_robot_data_payload_t;

typedef struct {
    atlas_robot_data_type_t type;
    atlas_robot_data_payload_t payload;
} atlas_robot_data_t;

typedef enum {
    ATLAS_ROBOT_PATH_TYPE_JOINTS,
    ATLAS_ROBOT_PATH_TYPE_CARTESIAN,
} atlas_robot_path_type_t;

typedef atlas_joints_path_t atlas_robot_path_payload_joints_t;
typedef atlas_cartesian_path_t atlas_robot_path_payload_cartesian_t;

typedef union {
    atlas_robot_path_payload_joints_t joints;
    atlas_robot_path_payload_cartesian_t cartesian;
} atlas_robot_path_payload_t;

typedef struct {
    atlas_robot_path_type_t type;
    atlas_robot_path_payload_t payload;
} atlas_robot_path_t;

typedef struct {
} atlas_robot_status_t;

typedef enum {
    ATLAS_ROBOT_STATE_IDLE,
    ATLAS_ROBOT_STATE_PATH,
    ATLAS_ROBOT_STATE_JOG,
    ATLAS_ROBOT_STATE_INVALID,
} atlas_robot_state_t;

#endif // ATLAS_CORE_ATLAS_ROBOT_H