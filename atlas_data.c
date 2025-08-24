#include "atlas_data.h"
#include "atlas_log.h"
#include "atlas_utility.h"
#include <stdint.h>

bool atlas_cartesian_data_is_equal(atlas_cartesian_data_t const* data1,
                                   atlas_cartesian_data_t const* data2)
{
    ATLAS_ASSERT(data1 != NULL);
    ATLAS_ASSERT(data2 != NULL);

    return data1->position.x == data2->position.x &&
           data1->position.y == data2->position.y &&
           data1->position.z == data2->position.z &&
           data1->orientation.x == data2->orientation.x &&
           data1->orientation.y == data2->orientation.y &&
           data1->orientation.z == data2->orientation.z;
}

bool atlas_joints_data_is_equal(atlas_joints_data_t const* data1,
                                atlas_joints_data_t const* data2)
{
    ATLAS_ASSERT(data1 != NULL);
    ATLAS_ASSERT(data2 != NULL);

    for (uint8_t num = 0; num < ATLAS_JOINT_NUM; ++num) {
        if (data1->positions[num] != data2->positions[num]) {
            return false;
        }
    }

    return true;
}

void atlas_cartesian_data_print(atlas_cartesian_data_t const* data)
{
    ATLAS_ASSERT(data != NULL);

    atlas_log(
        "position x: %f, y: %f, z: %f orientation x: %f, y: %f, z: %f\n\r",
        data->position.x,
        data->position.y,
        data->position.z,
        data->orientation.x,
        data->orientation.y,
        data->orientation.z);
}

void atlas_joints_data_print(atlas_joints_data_t const* data)
{
    ATLAS_ASSERT(data != NULL);

    atlas_log("position 1: %f, 2: %f, 3: %f, 4: %f, 5: %f, 6: %f\n\r",
              data->positions[ATLAS_JOINT_NUM_1],
              data->positions[ATLAS_JOINT_NUM_2],
              data->positions[ATLAS_JOINT_NUM_3],
              data->positions[ATLAS_JOINT_NUM_4],
              data->positions[ATLAS_JOINT_NUM_5],
              data->positions[ATLAS_JOINT_NUM_6]);
}
