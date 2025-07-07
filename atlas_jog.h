#ifndef ATLAS_CORE_ATLAS_JOG_H
#define ATLAS_CORE_ATLAS_JOG_H

#include <atlas_data.h>

typedef enum {
    ATLAS_JOG_TYPE_JOINTS,
    ATLAS_JOG_TYPE_CARTESIAN,
} atlas_jog_type_t;

typedef atlas_joints_data_t atlas_jog_payload_joints_t;
typedef atlas_cartesian_data_t atlas_jog_payload_cartesian_t;

typedef union {
    atlas_jog_payload_joints_t joints;
    atlas_jog_payload_cartesian_t cartesian;
} atlas_jog_payload_t;

typedef struct {
    atlas_jog_type_t type;
    atlas_jog_payload_t payload;
} atlas_jog_t;

#endif // ATLAS_CORE_ATLAS_JOG_H
