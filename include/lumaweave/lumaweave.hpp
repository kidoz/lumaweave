#ifndef LUMAWEAVE_LUMAWEAVE_HPP
#define LUMAWEAVE_LUMAWEAVE_HPP

#include <lumaweave/lumaweave.h>

#include <utility>

namespace lumaweave {

class context final {
  public:
    context() noexcept {
        const lw_context_desc desc = LW_CONTEXT_DESC_INIT;
        result_ = lwCreateContext(&desc, &handle_);
    }

    ~context() {
        lwDestroyContext(handle_);
    }

    context(const context&) = delete;
    context& operator=(const context&) = delete;

    context(context&& other) noexcept
        : handle_(std::exchange(other.handle_, nullptr)),
          result_(std::exchange(other.result_, LW_ERROR_INVALID_ARGUMENT)) {}

    context& operator=(context&& other) noexcept {
        if (this != &other) {
            lwDestroyContext(handle_);
            handle_ = std::exchange(other.handle_, nullptr);
            result_ = std::exchange(other.result_, LW_ERROR_INVALID_ARGUMENT);
        }
        return *this;
    }

    [[nodiscard]] explicit operator bool() const noexcept {
        return result_ == LW_OK;
    }
    [[nodiscard]] lw_result result() const noexcept {
        return result_;
    }
    [[nodiscard]] lw_context get() const noexcept {
        return handle_;
    }

  private:
    lw_context handle_ = nullptr;
    lw_result result_ = LW_ERROR_INTERNAL;
};

} // namespace lumaweave

#endif
