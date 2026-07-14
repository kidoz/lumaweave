# Contributing to LumaWeave

Keep changes small, reviewable, and aligned with the project's current roadmap and
documented architecture.

Before submitting a change, configure a clean CPU-only build and run:

```sh
meson compile -C build
meson test -C build --print-errorlogs
```

Format only touched C, C++, and HLSL files. Do not introduce proprietary vendor code,
required ML runtimes, backend headers into the portable API, hidden GPU submission, or
per-frame allocation. Report GPU, quality, and performance validation only when it ran.
