#ifndef ATLAS_CORE_ATLAS_ROBOT_H
#define ATLAS_CORE_ATLAS_ROBOT_H

#include "atlas_data.h"
#include "atlas_path.h"
#include <stdint.h>

#define ATLAS_ROBOT_PATH_MAXLEN (10U)

typedef enum {
    ATLAS_ROBOT_DATA_TYPE_JOINTS,
    ATLAS_ROBOT_DATA_TYPE_CARTESIAN,
    ATLAS_ROBOT_DATA_TYPE_NONE,
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

typedef uint8_t atlas_robot_path_length_t;
typedef atlas_robot_data_t atlas_robot_path_point_t;

typedef struct {
    atlas_robot_path_length_t length;
    atlas_robot_path_point_t points[ATLAS_ROBOT_PATH_MAXLEN];
} atlas_robot_path_t;

typedef enum {
    ATLAS_ROBOT_STATE_IDLE,
    ATLAS_ROBOT_STATE_PATH,
    ATLAS_ROBOT_STATE_JOG,
    ATLAS_ROBOT_STATE_INVALID,
} atlas_robot_state_t;

bool atlas_robot_data_is_equal(atlas_robot_data_t const* data1,
                               atlas_robot_data_t const* data2);

void atlas_robot_data_print(atlas_robot_data_t const* data);

bool atlas_robot_data_to_string(atlas_robot_data_t const* data,
                                char* string,
                                size_t string_length);

bool atlas_robot_data_from_string(char const* string,
                                  size_t string_length,
                                  atlas_robot_data_t* data);

bool atlas_robot_path_is_equal(atlas_robot_path_t const* path1,
                               atlas_robot_path_t const* path2);

void atlas_robot_path_print(atlas_robot_path_t const* path);

bool atlas_robot_path_to_string(atlas_robot_path_t const* path,
                                char* string,
                                size_t string_length);

bool atlas_robot_path_from_string(char const* string,
                                  size_t string_length,
                                  atlas_robot_path_t* path);

#endif // ATLAS_CORE_ATLAS_ROBOT_H