#ifndef ATLAS_CORE_ATLAS_PACKET_H
#define ATLAS_CORE_ATLAS_PACKET_H

#include "atlas_data.h"
#include "atlas_path.h"
#include "atlas_state.h"

typedef enum {
    ATLAS_ROB_PACKET_TYPE_STATE,
    ATLAS_ROB_PACKET_TYPE_PATH,
    ATLAS_ROB_PACKET_TYPE_JOG,
    ATLAS_ROB_PACKET_TYPE_CONFIG,
} atlas_rob_packet_type_t;

typedef atlas_state_t atlas_rob_packet_payload_state_t;
typedef atlas_jog_t atlas_rob_packet_payload_jog_t;
typedef atlas_path_t atlas_rob_packet_payload_path_t;

typedef union {
    atlas_rob_packet_payload_state_t state;
    atlas_rob_packet_payload_jog_t jog;
    atlas_rob_packet_payload_path_t path;
} atlas_rob_packet_payload_t;

typedef struct {
    atlas_rob_packet_type_t type;
    atlas_rob_packet_payload_t payload;
} atlas_rob_packet_t;

typedef enum {
    ATLAS_HMI_PACKET_TYPE_STATE,
    ATLAS_HMI_PACKET_TYPE_DATA,
} atlas_hmi_packet_type_t;

typedef atlas_state_t atlas_hmi_packet_payload_state_t;
typedef atlas_data_t atlas_hmi_packet_payload_data_t;

typedef union {
    atlas_hmi_packet_payload_status_t status;
    atlas_hmi_packet_payload_data_t data;
} atlas_hmi_packet_payload_t;

typedef struct {
    atlas_hmi_packet_type_t type;
    atlas_hmi_packet_payload_t payload;
} atlas_hmi_packet_t;

#endif // ATLAS_CORE_ATLAS_PACKET_H