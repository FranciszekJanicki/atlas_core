#ifndef ATLAS_CORE_ATLAS_STATE_H
#define ATLAS_CORE_ATLAS_STATE_H

typedef enum {
    ATLAS_STATE_TYPE_IDLE,
    ATLAS_STATE_TYPE_JOG,
    ATLAS_STATE_TYPE_PATH,
    ATLAS_STATE_TYPE_ERROR,
} atlas_state_type_t;

typedef struct {
    uint32_t timestamp;
    atlas_joints_data_t joints_data;
    atlas_cartesian_data_t cartesian_data;
} atlas_state_payload_t;

typedef struct {
    atlas_state_type_t type;
    atlas_state_payload_t payload;
} atlas_state_t;

#endif // ATLAS_CORE_ATLAS_STATE_H