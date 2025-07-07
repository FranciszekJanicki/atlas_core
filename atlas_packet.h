#ifndef ATLAS_CORE_ATLAS_PACKET_H
#define ATLAS_CORE_ATLAS_PACKET_H

#include "atlas_jog.h"
#include "atlas_path.h"

typedef enum {
    ATLAS_PACKET_TYPE_JOG,
    ATLAS_PACKET_TYPE_PATH,
    ATLAS_PACKET_TYPE_STATE,
} atlas_packet_type_t;

typedef struct {
    atlas_jog_t jog;
} atlas_packet_payload_jog_t;

typedef struct {
    atlas_path_t path;
} atlas_packet_payload_path_t;

typedef struct {
    atlas_state_t state;
} atlas_packet_payload_state_t;

typedef union {
    atlas_packet_payload_state_t state;
    atlas_packet_payload_jog_t jog;
    atlas_packet_payload_path_t path;
} atlas_packet_payload_t;

typedef struct {
    atlas_packet_type_t type;
    atlas_packet_payload_t payload;
} atlas_packet_t;

#endif // ATLAS_CORE_ATLAS_PACKET_H