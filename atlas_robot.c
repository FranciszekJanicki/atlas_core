#include "atlas_robot.h"
#include "atlas_data.h"
#include "atlas_joint.h"
#include "atlas_log.h"
#include "atlas_utility.h"
#include <stdint.h>
#include <string.h>

bool atlas_robot_data_is_equal(atlas_robot_data_t const* data1,
                               atlas_robot_data_t const* data2)
{
    ATLAS_ASSERT(data1 != NULL);
    ATLAS_ASSERT(data2 != NULL);

    if (data1->type != data2->type) {
        return false;
    }

    if (data1->type == ATLAS_ROBOT_DATA_TYPE_JOINTS) {
        return atlas_joints_data_is_equal(&data1->payload.joints,
                                          &data2->payload.joints);
    } else if (data1->type == ATLAS_ROBOT_DATA_TYPE_CARTESIAN) {
        return atlas_cartesian_data_is_equal(&data1->payload.cartesian,
                                             &data2->payload.cartesian);
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

bool atlas_robot_data_to_string(atlas_robot_data_t const* data,
                                char* string,
                                size_t string_length)
{
    ATLAS_ASSERT(data != NULL);
    ATLAS_ASSERT(string != NULL);
    ATLAS_ASSERT(string_length > 0UL);

    if (data->type == ATLAS_ROBOT_DATA_TYPE_JOINTS) {
        return atlas_joints_data_to_string(&data->payload.joints,
                                           string,
                                           string_length);
    } else if (data->type == ATLAS_ROBOT_DATA_TYPE_CARTESIAN) {
        return atlas_cartesian_data_to_string(&data->payload.cartesian,
                                              string,
                                              string_length);
    }

    return false;
}

bool atlas_robot_data_from_string(char const* string,
                                  size_t string_length,
                                  atlas_robot_data_t* data)
{
    ATLAS_ASSERT(data != NULL);
    ATLAS_ASSERT(string != NULL);
    ATLAS_ASSERT(string_length > 0UL);

    if (strncmp(string, "JOINTS: ", strlen("JOINTS: ")) == 0) {
        data->type = ATLAS_ROBOT_DATA_TYPE_JOINTS;

        return atlas_joints_data_from_string(string,
                                             string_length,
                                             &data->payload.joints);

    } else if (strncmp(string, "CARTESIAN: ", strlen("CARTESIAN: ")) ==0) {
        data->type = ATLAS_ROBOT_DATA_TYPE_CARTESIAN;

        return atlas_cartesian_data_from_string(string,
                                                string_length,
                                                &data->payload.cartesian);
    }

    return false;
}

bool atlas_robot_path_is_equal(atlas_robot_path_t const* path1,
                               atlas_robot_path_t const* path2)
{
    ATLAS_ASSERT(path1 != NULL);
    ATLAS_ASSERT(path2 != NULL);

    if (path1->length != path2->length) {
        return false;
    }

    for (atlas_robot_path_length_t i = 0U; i < path1->length; ++i) {
        if (!atlas_robot_data_is_equal(&path1->points[i], &path2->points[i])) {
            return false;
        }
    }

    return true;
}

void atlas_robot_path_print(atlas_robot_path_t const* path)
{
    ATLAS_ASSERT(path != NULL);

    for (uint8_t i = 0U; i < path->length; ++i) {
        atlas_robot_data_print(&path->points[i]);
    }
}

bool atlas_robot_path_to_string(atlas_robot_path_t const* path,
                                char* string,
                                size_t string_length)
{
    ATLAS_ASSERT(path != NULL);
    ATLAS_ASSERT(string != NULL);
    ATLAS_ASSERT(string_length > 0UL);

    size_t used_length = 0UL;
    for (atlas_path_length_t i = 0U; i < path->length; ++i) {
        if (used_length >= string_length) {
            return false;
        }

        char* endline = strchr(string + used_length, '\n');
        char* line = string + used_length;
        size_t line_length = endline - line;

        if (!atlas_robot_data_to_string(&path->points[i],
                                        string + used_length,
                                        string_length - used_length)) {
            return false;
        }

        strncat(line, "\n", string_length - used_length);
        used_length += line_length + 1UL;
    }

    string[used_length] = '\0';

    return true;
}

bool atlas_robot_path_from_string(char const* string,
                                  size_t string_length,
                                  atlas_robot_path_t* path)
{
    ATLAS_ASSERT(string != NULL);
    ATLAS_ASSERT(string_length > 0UL);
    ATLAS_ASSERT(path != NULL);

    size_t parsed_length = 0UL;
    for (atlas_path_length_t i = 0U; i < path->length; ++i) {
        if (parsed_length >= string_length) {
            return false;
        }

        char* endline = strchr(string + parsed_length, '\n');
        if (endline == NULL) {
            return true;
        }

        char* line = string + parsed_length;
        size_t line_length = endline - line;
        if (!atlas_robot_data_from_string(line,
                                          line_length,
                                          &path->points[i])) {
            return false;
        }

        parsed_length += line_length;
    }

    return true;
}
