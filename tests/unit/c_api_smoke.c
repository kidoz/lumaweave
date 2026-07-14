#include <lumaweave/lumaweave.h>

int lw_run_c_api_smoke(void) {
    lw_context context = NULL;
    lw_context_desc desc = LW_CONTEXT_DESC_INIT;

    if (lwCreateContext(NULL, &context) != LW_ERROR_INVALID_ARGUMENT || context != NULL) {
        return 1;
    }

    desc.struct_size = sizeof(desc) - 1;
    if (lwCreateContext(&desc, &context) != LW_ERROR_INVALID_ARGUMENT || context != NULL) {
        return 2;
    }

    desc.struct_size = sizeof(desc);
    desc.api_version = LW_API_VERSION + 1;
    if (lwCreateContext(&desc, &context) != LW_ERROR_INCOMPATIBLE_API || context != NULL) {
        return 3;
    }

    desc.api_version = LW_API_VERSION;
    if (lwCreateContext(&desc, NULL) != LW_ERROR_INVALID_ARGUMENT) {
        return 4;
    }

    if (lwCreateContext(&desc, &context) != LW_OK || context == NULL) {
        return 5;
    }

    lwDestroyContext(context);
    lwDestroyContext(NULL);
    return 0;
}
