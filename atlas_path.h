#ifndef ATLAS_CORE_ATLAS_PATH_H
#define ATLAS_CORE_ATLAS_PATH_H

#include "atlas_data.h"
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

#define ATLAS_PATH_MAX_LENGTH (10U)

typedef uint8_t atlas_path_length_t;

typedef struct {
    atlas_path_length_t length;
    atlas_joints_data_t points[ATLAS_PATH_MAX_LENGTH];
} atlas_joints_path_t;

typedef struct {
    atlas_path_length_t length;
    atlas_cartesian_data_t points[ATLAS_PATH_MAX_LENGTH];
} atlas_cartesian_path_t;

bool atlas_cartesian_path_is_equal(atlas_cartesian_path_t const* path1,
                                   atlas_cartesian_path_t const* path2);
bool atlas_joints_path_is_equal(atlas_joints_path_t const* path1,
                                atlas_joints_path_t const* path2);

void atlas_cartesian_path_print(atlas_cartesian_path_t const* path);
void atlas_joints_path_print(atlas_joints_path_t const* path);

bool atlas_cartesian_path_to_string(atlas_cartesian_path_t const* path,
                                    char* string,
                                    size_t string_length);
bool atlas_joints_path_to_string(atlas_joints_path_t const* path,
                                 char* string,
                                 size_t string_length);

bool atlas_cartesian_path_from_string(char const* string,
                                      size_t string_length,
                                      atlas_cartesian_path_t* path);
bool atlas_joints_path_from_string(char const* string,
                                   size_t string_length,
                                   atlas_joints_path_t* path);

#endif // ATLAS_CORE_ATLAS_PATH_H
