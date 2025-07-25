#include "atlas_robot.h"
#include "atlas_joint.h"
#include "atlas_log.h"
#include "atlas_utility.h"
#include <stdint.h>

static bool atlas_robot_
_is_equal(
    atlas_robot_joints_data_t const* joints1,
    atlas_robot_joints_data_t const* joints2)
{
    ATLAS_ASSERT(joints1 != NULL);
    ATLAS_ASSERT(joints2 != NULL);

    for (uint8_t num = 0; num < ATLAS_JOINT_NUM; ++num) {
        if (joints1->positions[num] != joints2->positions[num]) {
            return false;
        }
    }

    return true;
}

static bool atlas_robot_cartesian_data_is_equal(
    atlas_robot_cartesian_data_t const* cartesian1,
    atlas_robot_cartesian_data_t const* cartesian2)
{
    ATLAS_ASSERT(cartesian1 != NULL);
    ATLAS_ASSERT(cartesian2 != NULL);

    return cartesian1->payload.position.x == cartesian2->position.x &&
           cartesian1->position.y == cartesian2->position.y &&
           cartesian1->position.z == cartesian2->position.z &&
           cartesian1->orientation.x == cartesian2->orientation.x &&
           cartesian1->orientation.y == cartesian2->orientation.y &&
           cartesian1->orientation.z == cartesian2->orientation.z;
}

bool atlas_robot_data_is_equal(atlas_robot_data_t const* data1,
                               atlas_robot_data_t const* data2)
{
    ATLAS_ASSERT(data1 != NULL);
    ATLAS_ASSERT(data2 != NULL);

    if (data1->type == ATLAS_ROBOT_DATA_TYPE_JOINTS &&
        data2->type == ATLAS_ROBOT_DATA_TYPE_JOINTS) {
        return atlas_robot_joints_data_is_equal(&data1->payload.joints,
                                                &data2->payload.joints);
    }
}

static void atlas_robot_cartesian_data_print(
    atlas_robot_cartesian_data_t const* cartesian)
{
    ATLAS_ASSERT(cartesian != NULL);

    atlas_robot_log(
        "position x: %d, y: %d, z: %d orientation x: %d, y: %d, z: %d "
        "[deg * 100]\n\r",
        (int32_t)cartesian->position.x * 100,
        (int32_t)cartesian->position.y * 100,
        (int32_t)cartesian->position.z * 100,
        (int32_t)cartesian->orientation.x * 100,
        (int32_t)cartesian->orientation.y * 100,
        (int32_t)cartesian->orientation.z * 100);
}

static void atlas_robot_joints_data_print(
    atlas_robot_joints_data_t const* joints)
{
    ATLAS_ASSERT(joints != NULL);

    atlas_robot_log(
        "position 1: %d, 2: %d, 3: %d, 4: %d, 5: %d, 6: %d [deg * 100]\n\r",
        (int32_t)joints->positions[ATLAS_JOINT_NUM_1] * 100,
        (int32_t)joints->positions[ATLAS_JOINT_NUM_2] * 100,
        (int32_t)joints->positions[ATLAS_JOINT_NUM_3] * 100,
        (int32_t)joints->positions[ATLAS_JOINT_NUM_4] * 100,
        (int32_t)joints->positions[ATLAS_JOINT_NUM_5] * 100,
        (int32_t)joints->positions[ATLAS_JOINT_NUM_6] * 100);
}

void atlas_robot_data_print(atlas_robot_data_t const* data)
{
    ATLAS_ASSERT(data != NULL);

    if (data->type == ATLAS_ROBOT_DATA_TYPE_JOINTS) {
        atlas_robot_joints_data_print(&data->payload.joints);
    } else if (data->type == ATLAS_ROBOT_DATA_TYPE_CARTESIAN) {
        atlas_robot_cartesian_data_print(&data->payload.cartesian);
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
