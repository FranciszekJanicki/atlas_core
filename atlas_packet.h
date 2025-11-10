#ifndef ATLAS_CORE_ATLAS_PACKET_H
#define ATLAS_CORE_ATLAS_PACKET_H

#include "atlas_checksum.h"
#include "atlas_joint.h"
#include "atlas_robot.h"
#include "atlas_timestamp.h"

typedef enum {
    ATLAS_ROBOT_PACKET_TYPE_JOINT_RESPONSE,
} atlas_robot_packet_type_t;

#define ATLAS_ROBOT_PACKET_TYPE_OFFSET (0UL)
#define ATLAS_ROBOT_PACKET_TYPE_SIZE (sizeof(atlas_robot_packet_type_t))

typedef atlas_joint_num_t atlas_robot_packet_origin_t;

#define ATLAS_ROBOT_PACKET_ORIGIN_OFFSET \
    (ATLAS_ROBOT_PACKET_TYPE_OFFSET + ATLAS_ROBOT_PACKET_TYPE_SIZE)
#define ATLAS_ROBOT_PACKET_ORIGIN_SIZE (sizeof(atlas_robot_packet_origin_t))

typedef atlas_joint_response_t atlas_robot_packet_payload_joint_response_t;

typedef union {
    atlas_robot_packet_payload_joint_response_t joint_response;
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
    ATLAS_JOINT_PACKET_TYPE_JOINT_COMMAND,
} atlas_joint_packet_type_t;

#define ATLAS_JOINT_PACKET_TYPE_OFFSET (0UL)
#define ATLAS_JOINT_PACKET_TYPE_SIZE (sizeof(atlas_joint_packet_type_t))

typedef atlas_joint_num_t atlas_joint_packet_destination_t;

#define ATLAS_JOINT_PACKET_DESTINATION_OFFSET \
    (ATLAS_JOINT_PACKET_TYPE_OFFSET + ATLAS_JOINT_PACKET_TYPE_SIZE)
#define ATLAS_JOINT_PACKET_DESTINATION_SIZE \
    (sizeof(atlas_joint_packet_destination_t))

typedef atlas_joint_command_t atlas_joint_packet_payload_joint_command_t;

typedef union {
    atlas_joint_packet_payload_joint_command_t joint_command;
} atlas_joint_packet_payload_t;

#define ATLAS_JOINT_PACKET_PAYLOAD_OFFSET    \
    (ATLAS_JOINT_PACKET_DESTINATION_OFFSET + \
     ATLAS_JOINT_PACKET_DESTINATION_SIZE)
#define ATLAS_JOINT_PACKET_PAYLOAD_SIZE (sizeof(atlas_joint_packet_payload_t))

typedef atlas_timestamp_t atlas_joint_packet_timestamp_t;

#define ATLAS_JOINT_PACKET_TIMESTAMP_OFFSET \
    (ATLAS_JOINT_PACKET_PAYLOAD_OFFSET + ATLAS_JOINT_PACKET_PAYLOAD_SIZE)
#define ATLAS_JOINT_PACKET_TIMESTAMP_SIZE \
    (sizeof(atlas_joint_packet_timestamp_t))

typedef struct {
    atlas_joint_packet_type_t type;
    atlas_joint_packet_destination_t destination;
    atlas_joint_packet_payload_t payload;
    atlas_joint_packet_timestamp_t timestamp;
} atlas_joint_packet_t;

#define ATLAS_JOINT_PACKET_SIZE                                           \
    (ATLAS_JOINT_PACKET_TYPE_SIZE + ATLAS_JOINT_PACKET_DESTINATION_SIZE + \
     ATLAS_JOINT_PACKET_PAYLOAD_SIZE + ATLAS_JOINT_PACKET_TIMESTAMP_SIZE)

typedef atlas_checksum_t atlas_joint_packet_checksum_t;

#define ATLAS_JOINT_PACKET_CHECKSUM_OFFSET (ATLAS_JOINT_PACKET_SIZE)
#define ATLAS_JOINT_PACKET_CHECKSUM_SIZE (sizeof(atlas_joint_packet_checksum_t))

#define ATLAS_JOINT_PACKET_WITH_CHECKSUM_SIZE \
    (ATLAS_JOINT_PACKET_SIZE + ATLAS_JOINT_PACKET_CHECKSUM_SIZE)

void atlas_robot_packet_encode_binary(
    atlas_robot_packet_t const* packet,
    uint8_t (*buffer)[ATLAS_ROBOT_PACKET_SIZE]);
void atlas_robot_packet_decode_binary(
    const uint8_t (*buffer)[ATLAS_ROBOT_PACKET_SIZE],
    atlas_robot_packet_t* packet);

void atlas_robot_packet_encode_binary_with_checksum(
    atlas_robot_packet_t const* packet,
    uint8_t (*buffer)[ATLAS_ROBOT_PACKET_WITH_CHECKSUM_SIZE]);
void atlas_robot_packet_decode_binary_with_checksum(
    const uint8_t (*buffer)[ATLAS_ROBOT_PACKET_WITH_CHECKSUM_SIZE],
    atlas_robot_packet_t* packet);

void atlas_joint_packet_encode_binary(
    atlas_joint_packet_t const* packet,
    uint8_t (*buffer)[ATLAS_JOINT_PACKET_SIZE]);
void atlas_joint_packet_decode_binary(
    const uint8_t (*buffer)[ATLAS_JOINT_PACKET_SIZE],
    atlas_joint_packet_t* packet);

void atlas_joint_packet_encode_binary_with_checksum(
    atlas_joint_packet_t const* packet,
    uint8_t (*buffer)[ATLAS_JOINT_PACKET_WITH_CHECKSUM_SIZE]);
void atlas_joint_packet_decode_binary_with_checksum(
    const uint8_t (*buffer)[ATLAS_JOINT_PACKET_WITH_CHECKSUM_SIZE],
    atlas_joint_packet_t* packet);

void atlas_robot_packet_print(atlas_robot_packet_t const* packet);
void atlas_joint_packet_print(atlas_joint_packet_t const* packet);

void atlas_robot_packet_dump(atlas_robot_packet_t const* packet);
void atlas_joint_packet_dump(atlas_joint_packet_t const* packet);

#endif // ATLAS_CORE_ATLAS_PACKET_H
