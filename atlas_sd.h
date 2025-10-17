#ifndef ATLAS_CORE_ATLAS_SD_H
#define ATLAS_CORE_ATLAS_SD_H

#include "atlas_robot.h"

#define ATLAS_SD_PATH_FILENAME_MAXLEN (100U)
#define ATLAS_SD_PATH_DIRNAME_MAXLEN (100U)
#define ATLAS_SD_MOUNT_POINT_MAXLEN (20U)
#define ATLAS_SD_CARD_BUFFER_SIZE (1000U)

typedef struct {
    char dirname[ATLAS_SD_PATH_DIRNAME_MAXLEN];
    char filename[ATLAS_SD_PATH_FILENAME_MAXLEN];
} atlas_sd_path_t;

typedef void* atlas_sd_filesystem_t;
typedef char atlas_sd_mount_point_t[ATLAS_SD_MOUNT_POINT_MAXLEN];

typedef enum {
    ATLAS_SD_COMMAND_TYPE_MOUNT_CARD,
    ATLAS_SD_COMMAND_TYPE_UNMOUNT_CARD,
    ATLAS_SD_COMMAND_TYPE_SAVE_PATH,
    ATLAS_SD_COMMAND_TYPE_LOAD_PATH,
    ATLAS_SD_COMMAND_TYPE_REMOVE_PATH,
} atlas_sd_command_type_t;

typedef struct {
    atlas_sd_mount_point_t mount_point;
} atlas_sd_command_payload_mount_card_t;

typedef struct {
    atlas_sd_mount_point_t mount_point;
} atlas_sd_command_payload_unmount_card_t;

typedef struct {
    atlas_sd_path_t sd_path;
    atlas_robot_path_t robot_path;
} atlas_sd_command_payload_save_path_t;

typedef struct {
    atlas_sd_path_t sd_path;
} atlas_sd_command_payload_load_path_t;

typedef struct {
    atlas_sd_path_t sd_path;
} atlas_sd_command_payload_remove_path_t;

typedef union {
    atlas_sd_command_payload_mount_card_t mount_card;
    atlas_sd_command_payload_unmount_card_t unmount_card;
    atlas_sd_command_payload_save_path_t save_path;
    atlas_sd_command_payload_load_path_t load_path;
    atlas_sd_command_payload_remove_path_t remove_path;
} atlas_sd_command_payload_t;

typedef struct {
    atlas_sd_command_type_t type;
    atlas_sd_command_payload_t payload;
} atlas_sd_command_t;

typedef enum {
    ATLAS_SD_RESPONSE_TYPE_CARD_MOUNTED,
    ATLAS_SD_RESPONSE_TYPE_CARD_UNMOUNTED,
    ATLAS_SD_RESPONSE_TYPE_PATH_SAVED,
    ATLAS_SD_RESPONSE_TYPE_PATH_LOADED,
    ATLAS_SD_RESPONSE_TYPE_PATH_REMOVED,
} atlas_sd_response_type_t;

typedef struct {
    bool success;
} atlas_sd_response_payload_card_mounted_t;

typedef struct {
    bool success;
} atlas_sd_response_payload_card_unmounted_t;

typedef struct {
    bool success;
} atlas_sd_response_payload_path_saved_t;

typedef struct {
    bool success;
    atlas_robot_path_t robot_path;
} atlas_sd_response_payload_path_loaded_t;

typedef struct {
    bool success;
} atlas_sd_response_payload_path_removed_t;

typedef union {
    atlas_sd_response_payload_card_unmounted_t card_mounted;
    atlas_sd_response_payload_card_unmounted_t card_unmounted;
    atlas_sd_response_payload_path_saved_t path_saved;
    atlas_sd_response_payload_path_loaded_t path_loaded;
    atlas_sd_response_payload_path_removed_t path_removed;
} atlas_sd_response_payload_t;

typedef struct {
    atlas_sd_response_type_t type;
    atlas_sd_response_payload_t payload;
} atlas_sd_response_t;

#endif // ATLAS_CORE_ATLAS_SD_H