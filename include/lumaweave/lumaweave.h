#ifndef LUMAWEAVE_LUMAWEAVE_H
#define LUMAWEAVE_LUMAWEAVE_H

#include <stddef.h>
#include <stdint.h>

#include <lumaweave/version.h>

#if defined(_WIN32) && !defined(LW_STATIC)
#if defined(LW_BUILDING_LIBRARY)
#define LW_API __declspec(dllexport)
#else
#define LW_API __declspec(dllimport)
#endif
#else
#define LW_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lw_context_t* lw_context;

typedef enum lw_result {
    LW_OK = 0,
    LW_ERROR_INVALID_ARGUMENT = 1,
    LW_ERROR_INCOMPATIBLE_API = 2,
    LW_ERROR_OUT_OF_MEMORY = 3,
    LW_ERROR_INTERNAL = 4
} lw_result;

typedef struct lw_context_desc {
    size_t struct_size;
    uint32_t api_version;
} lw_context_desc;

#define LW_CONTEXT_DESC_INIT {sizeof(lw_context_desc), LW_API_VERSION}

LW_API lw_result lwCreateContext(const lw_context_desc* desc, lw_context* out_context);
LW_API void lwDestroyContext(lw_context context);

#ifdef __cplusplus
}
#endif

#endif
