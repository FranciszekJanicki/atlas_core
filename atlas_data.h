#ifndef ATLAS_CORE_ATLAS_DATA_H
#define ATLAS_CORE_ATLAS_DATA_H

#include "atlas_joint.h"
#include "atlas_types.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    float32_t positions[ATLAS_JOINT_NUM];
} atlas_joints_data_t;

typedef struct {
    vec3_float32_t position;
    vec3_float32_t orientation;
} atlas_cartesian_data_t;

bool atlas_cartesian_data_is_equal(atlas_cartesian_data_t const* data1,
                                   atlas_cartesian_data_t const* data2);
bool atlas_joints_data_is_equal(atlas_joints_data_t const* data1,
                                atlas_joints_data_t const* data2);

void atlas_cartesian_data_print(atlas_cartesian_data_t const* data);
void atlas_joints_data_print(atlas_joints_data_t const* data);

bool atlas_cartesian_data_to_string(atlas_cartesian_data_t const* data,
                                    char* string,
                                    size_t string_length);
bool atlas_joints_data_to_string(atlas_joints_data_t const* data,
                                 char* string,
                                 size_t string_length);

bool atlas_cartesian_data_from_string(const char* string,
                                      size_t string_length,
                                      atlas_cartesian_data_t* data);
bool atlas_joints_data_from_string(const char* string,
                                   size_t string_length,
                                   atlas_joints_data_t* data);

#endif // ATLAS_CORE_ATLAS_DATA_H
