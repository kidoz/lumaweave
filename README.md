# LumaWeave

LumaWeave is an open-source, cross-vendor temporal image reconstruction library for
AMD and NVIDIA GPUs. Its baseline is an analytical temporal upscaler implemented in
portable compute shaders; it does not require a vendor ML runtime.

The project is in early development. The current increment provides the backend-neutral
C ABI and C++20 RAII wrapper skeleton. Vulkan, Direct3D 12, shaders, and production
reconstruction are not implemented yet.

## Build

Meson 1.3 or newer and a C/C++ compiler are required. A CPU-only build does not require
a GPU SDK. Tests use the pinned Catch2 3.15.0 fallback when no compatible system package
is installed:

```sh
meson setup build -Dvulkan=disabled -Ddx12=disabled -Dtests=true
meson compile -C build
meson test -C build --print-errorlogs
```

Feature switches are listed with `meson configure build`. Explicitly enabling an
unavailable GPU API is a configuration error rather than a silent downgrade.
Distribution builders can add `--wrap-mode=nofallback` to require system dependencies;
configuration then fails if Catch2 3.15.0 is unavailable.

## Scope

LumaWeave is an independent project, not an implementation of a vendor upscaler. Frame
generation and optional neural reconstruction are outside the analytical MVP.

## License

MIT. See [LICENSE](LICENSE).
