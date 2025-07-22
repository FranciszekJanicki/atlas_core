#include "atlas_timestamp.h"
#include "atlas_utility.h"
#include <stdio.h>
#include <stdlib.h>

void atlas_timestamp_print(atlas_timestamp_t const* timestamp)
{
    char* string;
    size_t string_len;
    bool used_malloc;

    atlas_timestamp_to_string(timestamp, &string, &string_len, &used_malloc);
    atlas_log("%s\n\r", string);

    if (used_malloc) {
        free(string);
    }
}

bool atlas_timestamp_to_string(atlas_timestamp_t const* timestamp,
                               char** string,
                               size_t* string_len,
                               bool* used_malloc)
{
    ATLAS_ASSERT(timestamp != NULL);
    ATLAS_ASSERT(string != NULL);
    ATLAS_ASSERT(string_len != NULL);
    ATLAS_ASSERT(used_malloc != NULL);

    if (timestamp->hours >= 24U || timestamp->minutes >= 60U ||
        timestamp->seconds >= 60U) {
        return false;
    }

    static char buffer[100];

    size_t needed_len = snprintf(NULL,
                                 0UL,
                                 "%u:%u:%u",
                                 timestamp->hours,
                                 timestamp->minutes,
                                 timestamp->seconds) +
                        1UL;

    if (needed_len < sizeof(buffer)) {
        *string = buffer;
        *string_len = sizeof(buffer);
        *used_malloc = false;
    } else {
        *string = calloc(sizeof(char), needed_len);
        *string_len = needed_len;
        *used_malloc = true;
    }

    if (*string == NULL) {
        return false;
    }

    size_t written_len = snprintf(*string,
                                  *string_len,
                                  "%u:%u:%u",
                                  timestamp->hours,
                                  timestamp->minutes,
                                  timestamp->seconds);

    return written_len == needed_len - 1UL;
}