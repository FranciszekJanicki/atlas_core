add_library(atlas_core STATIC)

target_sources(atlas_core PRIVATE
    atlas_err.c
    atlas_log.c
    atlas_data.c
    atlas_path.c
    atlas_packet.c
    atlas_timestamp.c
    atlas_checksum.c
    atlas_joint.c
)

target_include_directories(atlas_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(atlas_core PUBLIC
    stm32cubemx
    utility
)

target_compile_options(atlas_core PUBLIC
    -std=c23
    -Wall
    -Wextra
    -Wconversion
    -Wshadow
    -Wpedantic
    -Wnarrowing
    -Waddress
    -pedantic
    -Wdeprecated
    -Wsign-conversion
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
    -Wcast-align
    -Wformat=2
    -Wformat-security
    -Wmissing-prototypes
    -Wmissing-declarations
    -Wstrict-prototypes
    -Wold-style-definition
    -Wundef
    -Wvla
    -Wpointer-arith
    -Wstrict-aliasing=2
)
