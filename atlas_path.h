#ifndef ATLAS_CORE_ATLAS_PATH_H
#define ATLAS_CORE_ATLAS_PATH_H

#include "atlas_data.h"
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

#define ATLAS_CARTESIAN_PATH_MAX_POINTS (10U)
#define ATLAS_JOINTS_PATH_MAX_POINTS (10U)

typedef struct {
    atlas_joints_data_t points[ATLAS_JOINTS_PATH_MAX_POINTS];
} atlas_joints_path_t;

typedef struct {
    atlas_cartesian_data_t points[ATLAS_CARTESIAN_PATH_MAX_POINTS];
} atlas_cartesian_path_t;

bool atlas_cartesian_path_is_equal(atlas_cartesian_path_t const* path1,
                                   atlas_cartesian_path_t const* path2);
bool atlas_joints_path_is_equal(atlas_joints_path_t const* path1,
                                atlas_joints_path_t const* path2);

void atlas_cartesian_path_print(atlas_cartesian_path_t const* path);
void atlas_joints_path_print(atlas_joints_path_t const* path);

#endif // ATLAS_CORE_ATLAS_PATH_H
