#ifndef ATLAS_CORE_ATLAS_STATUS_H
#define ATLAS_CORE_ATLAS_STATUS_H

#include <stdint.h>

typedef struct {
    uint32_t timestamp;
    atlas_data_t data;
    atlas_state_t state;
    atlas_path_t path;
} atlas_status_t;

#endif // ATLAS_CORE_ATLAS_STATUS_H