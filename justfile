build_dir := env_var_or_default("BUILD_DIR", "buildDir")

# Format project C, C++, and shared-HLSL sources in place.
format:
    #!/usr/bin/env bash
    set -euo pipefail
    files=()
    while IFS= read -r -d '' file; do
        files+=("$file")
    done < <(git ls-files --cached --others --exclude-standard -z -- \
        '*.c' '*.cc' '*.cpp' '*.cxx' \
        '*.h' '*.hh' '*.hpp' '*.hxx' \
        '*.hlsl' '*.hlsli' \
        ':!subprojects/**')
    if ((${#files[@]})); then
        clang-format --style=file -i -- "${files[@]}"
    fi

# Run clang-tidy using Meson's compilation database (override with BUILD_DIR=...).
lint:
    #!/usr/bin/env bash
    set -euo pipefail
    if [[ ! -f "{{ build_dir }}/compile_commands.json" ]]; then
        echo "error: {{ build_dir }}/compile_commands.json not found; configure Meson first" >&2
        exit 1
    fi
    files=()
    while IFS= read -r -d '' file; do
        files+=("$file")
    done < <(git ls-files --cached --others --exclude-standard -z -- \
        '*.c' '*.cc' '*.cpp' '*.cxx' \
        ':!subprojects/**')
    if ((${#files[@]})); then
        tidy_args=(-p "{{ build_dir }}")
        if [[ "$(uname -s)" == Darwin ]] && command -v xcrun >/dev/null; then
            tidy_args+=(--extra-arg=-isysroot --extra-arg="$(xcrun --show-sdk-path)")
        fi
        clang-tidy "${tidy_args[@]}" "${files[@]}"
    fi
