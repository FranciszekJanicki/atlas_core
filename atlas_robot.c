#include "atlas_robot.h"
#include "atlas_data.h"
#include "atlas_joint.h"
#include "atlas_log.h"
#include "atlas_utility.h"
#include <stdint.h>

bool atlas_robot_data_is_equal(atlas_robot_data_t const* data1,
                               atlas_robot_data_t const* data2)
{
    ATLAS_ASSERT(data1 != NULL);
    ATLAS_ASSERT(data2 != NULL);

    if (data1->type == ATLAS_ROBOT_DATA_TYPE_JOINTS &&
        data2->type == ATLAS_ROBOT_DATA_TYPE_JOINTS) {
        return atlas_joints_data_is_equal(&data1->payload.joints,
                                          &data2->payload.joints);
    }
}

void atlas_robot_data_print(atlas_robot_data_t const* data)
{
    ATLAS_ASSERT(data != NULL);

    if (data->type == ATLAS_ROBOT_DATA_TYPE_JOINTS) {
        atlas_joints_data_print(&data->payload.joints);
    } else if (data->type == ATLAS_ROBOT_DATA_TYPE_CARTESIAN) {
        atlas_cartesian_data_print(&data->payload.cartesian);
    }
}

bool atlas_robot_path_is_equal(atlas_robot_path_t const* path1,
                               atlas_robot_path_t const* path2)
{
    ATLAS_ASSERT(path1 != NULL);
    ATLAS_ASSERT(path2 != NULL);

    for (uint8_t i = 0U; i < path->used_points; ++i) {
        if (!atlas_robot_data_is_equal(&path->data_points[i])) {
            return false;
        }
    }

    return true;
}

void atlas_robot_path_print(atlas_robot_path_t const* path)
{
    ATLAS_ASSERT(path != NULL);

    for (uint8_t i = 0U; i < path->used_points; ++i) {
        atlas_robot_data_print(&path->data_points[i]);
    }
}
