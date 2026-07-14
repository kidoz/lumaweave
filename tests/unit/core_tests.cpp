#include <lumaweave/lumaweave.hpp>

#include <catch2/catch_test_macros.hpp>

#include <utility>

extern "C" int lw_run_c_api_smoke(void);

TEST_CASE("the C API is valid C and rejects incompatible descriptors", "[api]") {
    REQUIRE(lw_run_c_api_smoke() == 0);
}

TEST_CASE("the C++ context owns and transfers a C context", "[api][cpp]") {
    lumaweave::context first;
    REQUIRE(first);

    lumaweave::context second(std::move(first));
    REQUIRE(second);
}
