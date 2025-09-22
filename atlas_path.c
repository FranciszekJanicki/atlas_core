#include "atlas_path.h"
#include "atlas_data.h"
#include "atlas_utility.h"

bool atlas_cartesian_path_is_equal(atlas_cartesian_path_t const* path1,
                                   atlas_cartesian_path_t const* path2)
{
    ATLAS_ASSERT(path1 != NULL);
    ATLAS_ASSERT(path2 != NULL);

    if (path1->length != path2->length) {
        return false;
    }

    for (atlas_path_length_t i = 0U; i < path1->length; ++i) {
        if (!atlas_cartesian_data_is_equal(&path1->points[i],
                                           &path2->points[i])) {
            return false;
        }
    }

    return true;
}

bool atlas_joints_path_is_equal(atlas_joints_path_t const* path1,
                                atlas_joints_path_t const* path2)
{
    ATLAS_ASSERT(path1 != NULL);
    ATLAS_ASSERT(path2 != NULL);

    if (path1->length != path2->length) {
        return false;
    }

    for (atlas_path_length_t i = 0U; i < path1->length; ++i) {
        if (!atlas_joints_data_is_equal(&path1->points[i], &path2->points[i])) {
            return false;
        }
    }

    return true;
}

void atlas_cartesian_path_print(atlas_cartesian_path_t const* path)
{
    ATLAS_ASSERT(path != NULL);

    for (atlas_path_length_t i = 0U; i < path->length; ++i) {
        atlas_cartesian_data_print(&path->points[i]);
    }
}

void atlas_joints_path_print(atlas_joints_path_t const* path)
{
    ATLAS_ASSERT(path != NULL);

    for (atlas_path_length_t i = 0U; i < path->length; ++i) {
        atlas_joints_data_print(&path->points[i]);
    }
}
