#ifndef ATLAS_CORE_ATLAS_PACKET_H
#define ATLAS_CORE_ATLAS_PACKET_H

#include "atlas_data.h"
#include "atlas_path.h"
#include "atlas_state.h"

typedef enum {
    ATLAS_ROB_PACKET_TYPE_PATH_DATA,
    ATLAS_ROB_PACKET_TYPE_JOG_DATA,
    ATLAS_ROB_PACKET_TYPE_START_PATH,
    ATLAS_ROB_PACKET_TYPE_STOP_PATH,
    ATLAS_ROB_PACKET_TYPE_START_JOG,
    ATLAS_ROB_PACKET_TYPE_STOP_JOG,
} atlas_rob_packet_type_t;

typedef struct {
    atlas_joints_data_t data;
} atlas_rob_packet_payload_joints_data_t;

typedef struct {
    atlas_cartesian_data_t data;
} atlas_rob_packet_payload_cartesian_data_t;

typedef struct {
    atlas_joints_path_t path;
} atlas_rob_packet_payload_joints_path_t;

typedef struct {
    atlas_cartesian_path_t path;
} atlas_rob_packet_payload_cartesian_path_t;

typedef struct {
} atlas_rob_packet_payload_start_path_t;

typedef struct {
} atlas_rob_packet_payload_stop_path_t;

typedef struct {
} atlas_rob_packet_payload_start_jog_t;

typedef struct {
} atlas_rob_packet_payload_stop_jog_t;

typedef union {
    atlas_rob_packet_payload_joints_data_t joints_data;
    atlas_rob_packet_payload_cartesian_data_t cartesian_data;
    atlas_rob_packet_payload_joints_path_t joints_path;
    atlas_rob_packet_payload_cartesian_path_t cartesian_path;
    atlas_rob_packet_payload_start_path_t start_path;
    atlas_rob_packet_payload_stop_path_t stop_path;
    atlas_rob_packet_payload_start_jog_t start_jog;
    atlas_rob_packet_payload_stop_jog_t stop_jog;
} atlas_rob_packet_payload_t;

typedef struct {
    atlas_rob_packet_type_t type;
    atlas_rob_packet_payload_t payload;
} atlas_rob_packet_t;

typedef enum {
    ATLAS_HMI_PACKET_TYPE_MEAS_DATA,
} atlas_hmi_packet_type_t;

typedef atlas_data_t atlas_hmi_packet_payload_meas_data_t;

typedef union {
    atlas_hmi_packet_payload_meas_data_t meas_data;
} atlas_hmi_packet_payload_t;

typedef struct {
    atlas_hmi_packet_type_t type;
    atlas_hmi_packet_payload_t payload;
} atlas_hmi_packet_t;

#endif // ATLAS_CORE_ATLAS_PACKET_H