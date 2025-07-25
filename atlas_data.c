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

    atlas_log("position x: %d, y: %d, z: %d orientation x: %d, y: %d, z: %d "
              "[deg * 100]\n\r",
              (int32_t)data->position.x * 100,
              (int32_t)data->position.y * 100,
              (int32_t)data->position.z * 100,
              (int32_t)data->orientation.x * 100,
              (int32_t)data->orientation.y * 100,
              (int32_t)data->orientation.z * 100);
}

void atlas_joints_data_print(atlas_joints_data_t const* data)
{
    ATLAS_ASSERT(data != NULL);

    atlas_log(
        "position 1: %d, 2: %d, 3: %d, 4: %d, 5: %d, 6: %d [deg * 100]\n\r",
        (int32_t)data->positions[ATLAS_JOINT_NUM_1] * 100,
        (int32_t)data->positions[ATLAS_JOINT_NUM_2] * 100,
        (int32_t)data->positions[ATLAS_JOINT_NUM_3] * 100,
        (int32_t)data->positions[ATLAS_JOINT_NUM_4] * 100,
        (int32_t)data->positions[ATLAS_JOINT_NUM_5] * 100,
        (int32_t)data->positions[ATLAS_JOINT_NUM_6] * 100);
}
