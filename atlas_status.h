#ifndef ATLAS_CORE_ATLAS_STATUS_H
#define ATLAS_CORE_ATLAS_STATUS_H

#include "atlas_data.h"
#include "atlas_state.h"
#include <stdint.h>

typedef struct {
    uint32_t timestamp;
    atlas_state_t state;
    atlas_joints_data_t joints;
    atlas_cartesian_data_t cartesian;
} atlas_status_t;

#endif // ATLAS_CORE_ATLAS_STATUS_H