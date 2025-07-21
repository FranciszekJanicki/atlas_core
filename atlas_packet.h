#ifndef ATLAS_CORE_ATLAS_PACKET_H
#define ATLAS_CORE_ATLAS_PACKET_H

#include "atlas_data.h"
#include "atlas_path.h"
#include "atlas_timestamp.h"

typedef enum {
    ATLAS_ROBOT_PACKET_TYPE_JOINT_READY,
    ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT,
    ATLAS_ROBOT_PACKET_TYPE_JOINT_DATA,
} atlas_robot_packet_type_t;

typedef atlas_joint_num_t atlas_robot_packet_origin_t;

typedef atlas_joint_ready_t atlas_robot_packet_payload_joint_ready_t;
typedef atlas_joint_fault_t atlas_robot_packet_payload_joint_fault_t;
typedef atlas_joint_data_t atlas_robot_packet_payload_joint_data_t;

typedef union {
    atlas_robot_packet_payload_joint_data_t joint_data;
    atlas_robot_packet_payload_joint_fault_t joint_fault;
    atlas_robot_packet_payload_joint_ready_t joint_ready;
} atlas_robot_packet_payload_t;

#define ROBOT_PACKET_PAYLOAD_SIZE (sizeof(atlas_robot_packet_payload_t))

typedef struct {
    atlas_timestamp_t timestamp;
    atlas_robot_packet_type_t type;
    atlas_robot_packet_origin_t origin;
    atlas_robot_packet_payload_t payload;
} atlas_robot_packet_t;

#define ROBOT_PACKET_SIZE                                   \
    (sizeof(uint32_t) + sizeof(atlas_robot_packet_type_t) + \
     sizeof(atlas_robot_packet_origin_t) +                  \
     sizeof(atlas_robot_packet_payload_t))

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

#define JOINT_PACKET_PAYLOAD_SIZE (sizeof(atlas_joint_packet_payload_t))

typedef struct {
    atlas_timestamp_t timestamp;
    atlas_joint_packet_type_t type;
    atlas_joint_packet_payload_t payload;
} atlas_joint_packet_t;

#define JOINT_PACKET_SIZE                                   \
    (sizeof(uint32_t) + sizeof(atlas_joint_packet_type_t) + \
     sizeof(atlas_joint_packet_payload_t))

void atlas_robot_packet_encode(atlas_robot_packet_t const* packet,
                               uint8_t (*buffer)[ROBOT_PACKET_SIZE]);
void atlas_robot_packet_decode(const uint8_t (*buffer)[ROBOT_PACKET_SIZE],
                               atlas_robot_packet_t* packet);

void atlas_joint_packet_encode(atlas_joint_packet_t const* packet,
                               uint8_t (*buffer)[JOINT_PACKET_SIZE]);
void atlas_joint_packet_decode(const uint8_t (*buffer)[JOINT_PACKET_SIZE],
                               atlas_joint_packet_t* packet);

#endif // ATLAS_CORE_ATLAS_PACKET_H
