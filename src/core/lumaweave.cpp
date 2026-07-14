#include <lumaweave/lumaweave.h>

#include <new>

struct lw_context_t {};

extern "C" lw_result lwCreateContext(const lw_context_desc* desc, lw_context* out_context) {
    if (out_context == nullptr) {
        return LW_ERROR_INVALID_ARGUMENT;
    }
    *out_context = nullptr;

    if (desc == nullptr || desc->struct_size < sizeof(lw_context_desc)) {
        return LW_ERROR_INVALID_ARGUMENT;
    }
    if (desc->api_version != LW_API_VERSION) {
        return LW_ERROR_INCOMPATIBLE_API;
    }

    try {
        *out_context = new (std::nothrow) lw_context_t;
        return *out_context != nullptr ? LW_OK : LW_ERROR_OUT_OF_MEMORY;
    } catch (...) {
        return LW_ERROR_INTERNAL;
    }
}

extern "C" void lwDestroyContext(lw_context context) {
    delete context;
}
