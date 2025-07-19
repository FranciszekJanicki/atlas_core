#include "atlas_packet.h"
#include "atlas_utility.h"
#include "string.h"

// properly encode / decode array of uint8_t into packet struct
// and vice-versa. It is correct even if the layout of these types
// (the whole struct as well as members) is different on MCUs
// communicating using these packet types. No matter endian,
// no matter layout in memory, no matter sizeof and alignof,
// because it is done referring to each field independently
// and working on variable values (which do not change
// no matter endianess) and not done via pointer cast / memcpy / union.
// union / pointer cast / memcpy is good for reinterpreting memory
// when 100% sure about memory layout and endianess, which is not
// the case when sending reinterpreted / reinterpreting received
// bytes between different devices

static void atlas_robot_packet_timestamp_encode(uint32_t timestamp,
                                                uint8_t* buffer)
{
    buffer[0] = (timestamp >> 24U) & 0xFFU;
    buffer[1] = (timestamp >> 16U) & 0xFFU;
    buffer[2] = (timestamp >> 8U) & 0xFFU;
    buffer[3] = timestamp & 0xFFU;
}

static void atlas_robot_packet_type_encode(atlas_robot_packet_type_t type,
                                           uint8_t* buffer)
{
    buffer[0] = (type >> 24U) & 0xFFU;
    buffer[1] = (type >> 16U) & 0xFFU;
    buffer[2] = (type >> 8U) & 0xFFU;
    buffer[3] = type & 0xFFU;
}

static void atlas_robot_packet_origin_encode(atlas_robot_packet_origin_t origin,
                                             uint8_t* buffer)
{
    buffer[0] = (origin >> 24U) & 0xFFU;
    buffer[1] = (origin >> 16U) & 0xFFU;
    buffer[2] = (origin >> 8U) & 0xFFU;
    buffer[3] = origin & 0xFFU;
}

static void atlas_robot_packet_payload_joint_data_encode(
    atlas_robot_packet_payload_joint_data_t const* joint_data,
    uint8_t* buffer)
{
    uint32_t position_bits = *(uint32_t*)&joint_data->position;

    buffer[0] = (position_bits >> 24U) & 0xFFU;
    buffer[1] = (position_bits >> 16U) & 0xFFU;
    buffer[2] = (position_bits >> 8U) & 0xFFU;
    buffer[3] = position_bits & 0xFFU;
}

static void atlas_robot_packet_payload_joint_fault_encode(
    atlas_robot_packet_payload_joint_fault_t const* joint_fault,
    uint8_t* buffer)
{}

static void atlas_robot_packet_payload_joint_ready_encode(
    atlas_robot_packet_payload_joint_ready_t const* joint_ready,
    uint8_t* buffer)
{}

static void atlas_robot_packet_payload_encode(
    atlas_robot_packet_type_t type,
    atlas_robot_packet_payload_t const* payload,
    uint8_t* buffer)
{
    if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_DATA) {
        atlas_robot_packet_payload_joint_data_encode(&payload->joint_data,
                                                     buffer);
    } else if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT) {
        atlas_robot_packet_payload_joint_fault_encode(&payload->joint_fault,
                                                      buffer);
    } else if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_READY) {
        atlas_robot_packet_payload_joint_ready_encode(&payload->joint_ready,
                                                      buffer);
    }
}

void atlas_robot_packet_encode(atlas_robot_packet_t const* packet,
                               uint8_t (*buffer)[ROBOT_PACKET_SIZE])
{
    ATLAS_ASSERT(packet && buffer);

    uint8_t* timestamp_buffer = (uint8_t*)buffer;
    atlas_robot_packet_timestamp_encode(packet->timestamp, timestamp_buffer);

    uint8_t* type_buffer = timestamp_buffer + sizeof(uint32_t);
    atlas_robot_packet_type_encode(packet->type, type_buffer);

    uint8_t* origin_buffer = type_buffer + sizeof(atlas_robot_packet_type_t);
    atlas_robot_packet_origin_encode(packet->origin, origin_buffer);

    uint8_t* payload_buffer =
        origin_buffer + sizeof(atlas_robot_packet_origin_t);
    atlas_robot_packet_payload_encode(packet->type,
                                      &packet->payload,
                                      payload_buffer);
}

static void atlas_robot_packet_timestamp_decode(uint8_t const* buffer,
                                                uint32_t* timestamp)
{
    *timestamp = (((buffer[0] & 0xFFU) << 24U) | ((buffer[1] & 0xFFU) << 16U) |
                  ((buffer[2] & 0xFFU) << 8U) | (buffer[3] & 0xFFU));
}

static void atlas_robot_packet_type_decode(uint8_t const* buffer,
                                           atlas_robot_packet_type_t* type)
{
    *type = (((buffer[0] & 0xFFU) << 24U) | ((buffer[1] & 0xFFU) << 16U) |
             ((buffer[2] & 0xFFU) << 8U) | ((buffer[3] & 0xFFU)));
}

static void atlas_robot_packet_origin_decode(
    uint8_t* buffer,
    atlas_robot_packet_origin_t* origin)
{
    *origin = (((buffer[0] & 0xFFU) << 24U) | ((buffer[1] & 0xFFU) << 16U) |
               ((buffer[2] & 0xFFU) << 8U) | ((buffer[3] & 0xFFU)));
}

static void atlas_robot_packet_payload_joint_data_decode(
    uint8_t const* buffer,
    atlas_robot_packet_payload_joint_data_t* joint_data)
{
    uint32_t position_bits =
        (((buffer[0] & 0xFFU) << 24U) | ((buffer[1] & 0xFFU) << 16U) |
         ((buffer[2] & 0xFFU) << 8U) | (buffer[3] & 0xFFU));

    joint_data->position = *(float32_t*)&position_bits;
}

static void atlas_robot_packet_payload_joint_fault_decode(
    uint8_t const* buffer,
    atlas_robot_packet_payload_joint_fault_t* joint_fault)
{}

static void atlas_robot_packet_payload_joint_ready_decode(
    uint8_t const* buffer,
    atlas_robot_packet_payload_joint_ready_t* joint_ready)
{}

static void atlas_robot_packet_payload_decode(
    uint8_t const* buffer,
    atlas_robot_packet_type_t type,
    atlas_robot_packet_payload_t* payload)
{
    if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_DATA) {
        atlas_robot_packet_payload_joint_data_decode(buffer,
                                                     &payload->joint_data);
    } else if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_FAULT) {
        atlas_robot_packet_payload_joint_fault_decode(buffer,
                                                      &payload->joint_fault);
    } else if (type == ATLAS_ROBOT_PACKET_TYPE_JOINT_READY) {
        atlas_robot_packet_payload_joint_ready_decode(buffer,
                                                      &payload->joint_ready);
    }
}

void atlas_robot_packet_decode(const uint8_t (*buffer)[ROBOT_PACKET_SIZE],
                               atlas_robot_packet_t* packet)
{
    ATLAS_ASSERT(buffer && packet);

    uint8_t* timestamp_buffer = (uint8_t*)buffer;
    atlas_robot_packet_timestamp_decode(timestamp_buffer, &packet->timestamp);

    uint8_t* type_buffer = timestamp_buffer + sizeof(uint32_t);
    atlas_robot_packet_type_decode(type_buffer, &packet->type);

    uint8_t* origin_buffer = type_buffer + sizeof(atlas_robot_packet_type_t);
    atlas_robot_packet_origin_decode(origin_buffer, &packet->origin);

    uint8_t* payload_buffer =
        origin_buffer + sizeof(atlas_robot_packet_origin_t);
    atlas_robot_packet_payload_decode(payload_buffer,
                                      packet->type,
                                      &packet->payload);
}

void atlas_joint_packet_encode(atlas_joint_packet_t const* packet,
                               uint8_t (*buffer)[JOINT_PACKET_SIZE])
{}

void atlas_joint_packet_decode(const uint8_t (*buffer)[JOINT_PACKET_SIZE],
                               atlas_joint_packet_t* packet)
{}
