#include "atlas_path.h"
#include "atlas_data.h"
#include "atlas_utility.h"

bool atlas_cartesian_path_is_equal(atlas_cartesian_path_t const* path1,
                                   atlas_cartesian_path_t const* path2)
{
    ATLAS_ASSERT(path1 && path2);

    for (uint8_t num = 0U; num < ATLAS_CARTESIAN_PATH_MAX_POINTS; ++num) {
        if (!atlas_cartesian_data_is_equal(&path1->points[num], &path2->points[num])) {
            return false;
        }
    }

    return true;
}

bool atlas_joints_path_is_equal(atlas_joints_path_t const* path1, atlas_joints_path_t const* path2)
{
    ATLAS_ASSERT(path1 && path2);

    for (uint8_t num = 0U; num < ATLAS_JOINTS_PATH_MAX_POINTS; ++num) {
        if (!atlas_joints_data_is_equal(&path1->points[num], &path2->points[num])) {
            return false;
        }
    }

    return true;
}

void atlas_cartesian_path_print(atlas_cartesian_path_t const* path)
{
    ATLAS_ASSERT(path);

    for (uint8_t point = 0U; point < ATLAS_CARTESIAN_PATH_MAX_POINTS; ++point) {
        atlas_cartesian_data_print(&path->points[point]);
    }
}

void atlas_joints_path_print(atlas_joints_path_t const* path)
{
    ATLAS_ASSERT(path);

    for (uint8_t point = 0U; point < ATLAS_JOINTS_PATH_MAX_POINTS; ++point) {
        atlas_joints_data_print(&path->points[point]);
    }
}
