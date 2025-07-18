#ifndef ATLAS_CORE_ATLAS_TYPES_H
#define ATLAS_CORE_ATLAS_TYPES_H

#ifndef FLOAT32_T
#define FLOAT32_T
typedef float float32_t;
#endif

#ifndef VEC3_FLOAT32_T
#define VEC3_FLOAT32_T
typedef struct {
    float32_t x;
    float32_t y;
    float32_t z;
} vec3_float32_t;
#endif

#endif // ATLAS_CORE_ATLAS_TYPES_H