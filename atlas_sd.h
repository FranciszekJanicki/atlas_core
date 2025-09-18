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

typedef struct {
    atlas_sd_path_t sd_path;
    atlas_robot_path_t robot_path;
} atlas_sd_save_path_t;

typedef struct {
    sd_path_t sd_path;
} atlas_sd_load_path_t;

typedef struct {
    atlas_sd_path_t sd_path;
    atlas_robot_config_t robot_config;
} atlas_sd_save_config_t;

typedef struct {
    atlas_sd_path_t sd_path;
} atlas_sd_load_config_t;

typedef struct {
    atlas_sd_path_t sd_path;
} atlas_sd_remove_path_t;

typedef struct {
    atlas_sd_path_t sd_path;
} atlas_sd_remove_config_t;

#endif // ATLAS_CORE_ATLAS_SD_H