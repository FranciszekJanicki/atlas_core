#ifndef ATLAS_CORE_ATLAS_PACKET_H
#define ATLAS_CORE_ATLAS_PACKET_H

#include "atlas_checksum.h"
#include "atlas_joint.h"
#include "atlas_robot.h"
#include "atlas_timestamp.h"

typedef enum {
    ATLAS_ROBOT_PACKET_TYPE_JOINT_READY,
    ATLAS_ROBOT_PACKET_TYPE_JOINT_STARTED,
    ATLAS_ROBOT_PACKET_TYPE_JOINT_STOPPED,
    ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT,
    ATLAS_ROBOT_PACKET_TYPE_JOINT_MEASURE,
} atlas_robot_packet_type_t;

#define ATLAS_ROBOT_PACKET_TYPE_OFFSET (0UL)
#define ATLAS_ROBOT_PACKET_TYPE_SIZE (sizeof(atlas_robot_packet_type_t))

typedef atlas_joint_num_t atlas_robot_packet_origin_t;

#define ATLAS_ROBOT_PACKET_ORIGIN_OFFSET \
    (ATLAS_ROBOT_PACKET_TYPE_OFFSET + ATLAS_ROBOT_PACKET_TYPE_SIZE)
#define ATLAS_ROBOT_PACKET_ORIGIN_SIZE (sizeof(atlas_robot_packet_origin_t))

typedef atlas_joint_ready_t atlas_robot_packet_payload_joint_ready_t;
typedef atlas_joint_started_t atlas_robot_packet_payload_joint_started_t;
typedef atlas_joint_started_t atlas_robot_packet_payload_joint_stopped_t;
typedef atlas_joint_fault_t atlas_robot_packet_payload_joint_fault_t;
typedef atlas_joint_measure_t atlas_robot_packet_payload_joint_measure_t;

typedef union {
    atlas_robot_packet_payload_joint_ready_t joint_ready;
    atlas_robot_packet_payload_joint_started_t joint_started;
    atlas_robot_packet_payload_joint_stopped_t joint_stopped;
    atlas_robot_packet_payload_joint_fault_t joint_fault;
    atlas_robot_packet_payload_joint_measure_t joint_measure;
} atlas_robot_packet_payload_t;

#define ATLAS_ROBOT_PACKET_PAYLOAD_OFFSET \
    (ATLAS_ROBOT_PACKET_ORIGIN_OFFSET + ATLAS_ROBOT_PACKET_ORIGIN_SIZE)
#define ATLAS_ROBOT_PACKET_PAYLOAD_SIZE (sizeof(atlas_robot_packet_payload_t))

typedef atlas_timestamp_t atlas_robot_packet_timestamp_t;

#define ATLAS_ROBOT_PACKET_TIMESTAMP_OFFSET \
    (ATLAS_ROBOT_PACKET_PAYLOAD_OFFSET + ATLAS_ROBOT_PACKET_PAYLOAD_SIZE)
#define ATLAS_ROBOT_PACKET_TIMESTAMP_SIZE \
    (sizeof(atlas_robot_packet_timestamp_t))

typedef struct {
    atlas_robot_packet_type_t type;
    atlas_robot_packet_origin_t origin;
    atlas_robot_packet_payload_t payload;
    atlas_robot_packet_timestamp_t timestamp;
} atlas_robot_packet_t;

#define ATLAS_ROBOT_PACKET_SIZE                                      \
    (ATLAS_ROBOT_PACKET_TYPE_SIZE + ATLAS_ROBOT_PACKET_ORIGIN_SIZE + \
     ATLAS_ROBOT_PACKET_PAYLOAD_SIZE + ATLAS_ROBOT_PACKET_TIMESTAMP_SIZE)

typedef atlas_checksum_t atlas_robot_packet_checksum_t;

#define ATLAS_ROBOT_PACKET_CHECKSUM_OFFSET (ATLAS_ROBOT_PACKET_SIZE)
#define ATLAS_ROBOT_PACKET_CHECKSUM_SIZE (sizeof(atlas_robot_packet_checksum_t))

#define ATLAS_ROBOT_PACKET_WITH_CHECKSUM_SIZE \
    (ATLAS_ROBOT_PACKET_SIZE + ATLAS_ROBOT_PACKET_CHECKSUM_SIZE)

typedef enum {
    ATLAS_JOINT_PACKET_TYPE_JOINT_START,
    ATLAS_JOINT_PACKET_TYPE_JOINT_STOP,
    ATLAS_JOINT_PACKET_TYPE_JOINT_RESET,
    ATLAS_JOINT_PACKET_TYPE_JOINT_REFERENCE,
    ATLAS_JOINT_PACKET_TYPE_JOINT_PARAMETERS,
} atlas_joint_packet_type_t;

#define ATLAS_JOINT_PACKET_TYPE_OFFSET (0UL)
#define ATLAS_JOINT_PACKET_TYPE_SIZE (sizeof(atlas_joint_packet_type_t))

typedef atlas_joint_start_t atlas_joint_packet_payload_joint_start_t;
typedef atlas_joint_stop_t atlas_joint_packet_payload_joint_stop_t;
typedef atlas_joint_reset_t atlas_joint_packet_payload_joint_reset_t;
typedef atlas_joint_reference_t atlas_joint_packet_payload_joint_reference_t;
typedef atlas_joint_parameters_t atlas_joint_packet_payload_joint_parameters_t;

typedef union {
    atlas_joint_packet_payload_joint_start_t joint_start;
    atlas_joint_packet_payload_joint_stop_t joint_stop;
    atlas_joint_packet_payload_joint_reset_t joint_reset;
    atlas_joint_packet_payload_joint_reference_t joint_reference;
    atlas_joint_packet_payload_joint_parameters_t joint_parameters;
} atlas_joint_packet_payload_t;

#define ATLAS_JOINT_PACKET_PAYLOAD_OFFSET \
    (ATLAS_JOINT_PACKET_TYPE_OFFSET + ATLAS_JOINT_PACKET_TYPE_SIZE)
#define ATLAS_JOINT_PACKET_PAYLOAD_SIZE (sizeof(atlas_joint_packet_payload_t))

typedef atlas_timestamp_t atlas_joint_packet_timestamp_t;

#define ATLAS_JOINT_PACKET_TIMESTAMP_OFFSET \
    (ATLAS_JOINT_PACKET_PAYLOAD_OFFSET + ATLAS_JOINT_PACKET_PAYLOAD_SIZE)
#define ATLAS_JOINT_PACKET_TIMESTAMP_SIZE \
    (sizeof(atlas_joint_packet_timestamp_t))

typedef struct {
    atlas_joint_packet_type_t type;
    atlas_joint_packet_payload_t payload;
    atlas_joint_packet_timestamp_t timestamp;
} atlas_joint_packet_t;

#define ATLAS_JOINT_PACKET_SIZE                                       \
    (ATLAS_JOINT_PACKET_TYPE_SIZE + ATLAS_JOINT_PACKET_PAYLOAD_SIZE + \
     ATLAS_JOINT_PACKET_TIMESTAMP_SIZE)

typedef atlas_checksum_t atlas_joint_packet_checksum_t;

#define ATLAS_JOINT_PACKET_CHECKSUM_OFFSET (ATLAS_JOINT_PACKET_SIZE)
#define ATLAS_JOINT_PACKET_CHECKSUM_SIZE (sizeof(atlas_joint_packet_checksum_t))

#define ATLAS_JOINT_PACKET_WITH_CHECKSUM_SIZE \
    (ATLAS_JOINT_PACKET_SIZE + ATLAS_JOINT_PACKET_CHECKSUM_SIZE)

void atlas_robot_packet_encode(atlas_robot_packet_t const* packet,
                               uint8_t (*buffer)[ATLAS_ROBOT_PACKET_SIZE]);
void atlas_robot_packet_decode(const uint8_t (*buffer)[ATLAS_ROBOT_PACKET_SIZE],
                               atlas_robot_packet_t* packet);

void atlas_robot_packet_encode_with_checksum(
    atlas_robot_packet_t const* packet,
    uint8_t (*buffer)[ATLAS_ROBOT_PACKET_WITH_CHECKSUM_SIZE]);
void atlas_robot_packet_decode_with_checksum(
    const uint8_t (*buffer)[ATLAS_ROBOT_PACKET_WITH_CHECKSUM_SIZE],
    atlas_robot_packet_t* packet);

void atlas_joint_packet_encode(atlas_joint_packet_t const* packet,
                               uint8_t (*buffer)[ATLAS_JOINT_PACKET_SIZE]);
void atlas_joint_packet_decode(const uint8_t (*buffer)[ATLAS_JOINT_PACKET_SIZE],
                               atlas_joint_packet_t* packet);

void atlas_joint_packet_encode_with_checksum(
    atlas_joint_packet_t const* packet,
    uint8_t (*buffer)[ATLAS_JOINT_PACKET_WITH_CHECKSUM_SIZE]);
void atlas_joint_packet_decode_with_checksum(
    const uint8_t (*buffer)[ATLAS_JOINT_PACKET_WITH_CHECKSUM_SIZE],
    atlas_joint_packet_t* packet);

void atlas_robot_packet_print(atlas_robot_packet_t const* packet);
void atlas_joint_packet_print(atlas_joint_packet_t const* packet);

void atlas_robot_packet_dump(atlas_robot_packet_t const* packet);
void atlas_joint_packet_dump(atlas_joint_packet_t const* packet);

#endif // ATLAS_CORE_ATLAS_PACKET_H
