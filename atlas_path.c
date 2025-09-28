#include "atlas_path.h"
#include "atlas_data.h"
#include "atlas_utility.h"
#include <string.h>

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

bool atlas_cartesian_path_to_string(atlas_cartesian_path_t const* path,
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

        if (!atlas_cartesian_data_to_string(&path->points[i],
                                            string + used_length,
                                            string_length - used_length)) {
            return false;
        }

        strncat(line, string_length - used_length, "\n");
        used_length += line_length + 1UL;
    }

    string[used_length] = '\0';

    return true;
}

bool atlas_joints_path_to_string(atlas_joints_path_t const* path,
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

        if (!atlas_joints_data_to_string(&path->points[i],
                                         string + used_length,
                                         string_length - used_length)) {
            return false;
        }

        strncat(line, string_length - used_length, "\n");
        used_length += line_length + 1UL;
    }

    string[used_length] = '\0';

    return true;
}

bool atlas_cartesian_path_from_string(char const* string,
                                      size_t string_length,
                                      atlas_cartesian_path_t* path)
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
        if (!atlas_cartesian_data_from_string(line,
                                              line_length,
                                              &path->points[i])) {
            return false;
        }

        parsed_length += line_length;
    }

    return true;
}

bool atlas_joints_path_from_string(char const* string,
                                   size_t string_length,
                                   atlas_joints_path_t* path)
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
        if (!atlas_joints_data_from_string(line,
                                              line_length,
                                              &path->points[i])) {
            return false;
        }

        parsed_length += line_length;
    }

    return true;
}
