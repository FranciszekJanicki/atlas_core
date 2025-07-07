#ifndef ATLAS_CORE_ATLAS_PATH_H
#define ATLAS_CORE_ATLAS_PATH_H

#include "atlas_data.h"
#include <limits.h>
#include <stdint.h>

#define ATLAS_CARTESIAN_PATH_MAX_POINTS (10U)
#define ATLAS_JOINTS_PATH_MAX_POINTS (10U)

typedef enum {
    ATLAS_PATH_TYPE_JOINTS,
    ATLAS_PATH_TYPE_CARTESIAN,
} atlas_path_type_t;

typedef struct {
    atlas_joints_data_t points[ATLAS_JOINTS_PATH_MAX_POINTS];
} atlas_joints_path_t;

typedef struct {
    atlas_cartesian_data_t points[ATLAS_CARTESIAN_PATH_MAX_POINTS];
} atlas_cartesian_path_t;

typedef atlas_joints_path_t atlas_path_payload_joints_t;

typedef atlas_cartesian_path_t atlas_path_payload_cartesian_t;

typedef union {
    atlas_path_payload_joints_t joints;
    atlas_path_payload_cartesian_t cartesian;
} atlas_path_payload_t;

typedef struct {
    atlas_path_type_t type;
    atlas_path_payload_t payload;
} atlas_path_t;

void atlas_print_cartesian_path(atlas_cartesian_path_t const* path);
void atlas_print_joints_path(atlas_joints_path_t const* path);

#endif // ATLAS_CORE_ATLAS_PATH_H