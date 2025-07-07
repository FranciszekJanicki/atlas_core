#ifndef ATLAS_CORE_ATLAS_PACKET_H
#define ATLAS_CORE_ATLAS_PACKET_H

#include "atlas_data.h"
#include "atlas_path.h"
#include "atlas_status.h"

typedef enum {
    ATLAS_PACKET_ORIGIN_ROB,
    ATLAS_PACKET_ORIGIN_HMI,
} atlas_packet_origin_t;

typedef enum {
    ATLAS_PACKET_TYPE_STATUS,
    ATLAS_PACKET_TYPE_PATH,
    ATLAS_PACKET_TYPE_DATA,
} atlas_packet_type_t;

typedef atlas_status_t atlas_packet_payload_status_t;
typedef atlas_data_t atlas_packet_payload_data_t;
typedef atlas_path_t atlas_packet_payload_path_t;

typedef union {
    atlas_packet_payload_status_t status;
    atlas_packet_payload_data_t data;
    atlas_packet_payload_path_t path;
} atlas_packet_payload_t;

typedef struct {
    atlas_packet_type_t type;
    atlas_packet_origin_t origin;
    atlas_packet_payload_t payload;
} atlas_packet_t;

#endif // ATLAS_CORE_ATLAS_PACKET_H