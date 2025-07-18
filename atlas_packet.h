#ifndef ATLAS_CORE_ATLAS_PACKET_H
#define ATLAS_CORE_ATLAS_PACKET_H

#include "atlas_data.h"
#include "atlas_path.h"

typedef enum {
    ATLAS_ROBOT_PACKET_TYPE_JOINT_READY,
    ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT,
    ATLAS_ROBOT_PACKET_TYPE_JOINT_DATA,
} atlas_robot_packet_type_t;

typedef enum {
    ATLAS_ROBOT_PACKET_ORIGIN_JOINT_1 = ATLAS_JOINT_NUM_1,
    ATLAS_ROBOT_PACKET_ORIGIN_JOINT_2 = ATLAS_JOINT_NUM_2,
    ATLAS_ROBOT_PACKET_ORIGIN_JOINT_3 = ATLAS_JOINT_NUM_3,
    ATLAS_ROBOT_PACKET_ORIGIN_JOINT_4 = ATLAS_JOINT_NUM_4,
    ATLAS_ROBOT_PACKET_ORIGIN_JOINT_5 = ATLAS_JOINT_NUM_5,
    ATLAS_ROBOT_PACKET_ORIGIN_JOINT_6 = ATLAS_JOINT_NUM_6,
} atlas_robot_packet_origin_t;

typedef atlas_joint_ready_t atlas_robot_packet_payload_joint_ready_t;
typedef atlas_joint_fault_t atlas_robot_packet_payload_joint_fault_t;
typedef atlas_joint_data_t atlas_robot_packet_payload_joint_data_t;

typedef union {
    atlas_robot_packet_payload_joint_ready_t joint_ready;
    atlas_robot_packet_payload_joint_fault_t joint_fault;
    atlas_robot_packet_payload_joint_data_t joint_data;
} atlas_robot_packet_payload_t;

typedef struct {
    atlas_robot_packet_type_t type;
    atlas_robot_packet_origin_t origin;
    atlas_robot_packet_payload_t payload;
} atlas_robot_packet_t;

typedef enum {
    ATLAS_JOINT_PACKET_TYPE_JOINT_START,
    ATLAS_JOINT_PACKET_TYPE_JOINT_STOP,
    ATLAS_JOINT_PACKET_TYPE_JOINT_DATA,
} atlas_joint_packet_type_t;

typedef atlas_joint_start_t atlas_joint_packet_payload_joint_start_t;
typedef atlas_joint_stop_t atlas_joint_packet_payload_joint_stop_t;
typedef atlas_joint_data_t atlas_joint_packet_payload_joint_data_t;

typedef union {
    atlas_joint_packet_payload_joint_start_t joint_start;
    atlas_joint_packet_payload_joint_stop_t joint_stop;
    atlas_joint_packet_payload_joint_data_t joint_data;
} atlas_joint_packet_payload_t;

typedef struct {
    atlas_joint_packet_type_t type;
    atlas_joint_packet_payload_t payload;
} atlas_joint_packet_t;

#endif // ATLAS_CORE_ATLAS_PACKET_H
