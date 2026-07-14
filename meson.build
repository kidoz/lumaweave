project(
  'lumaweave',
  ['c', 'cpp'],
  version : '0.1.0',
  license : 'MIT',
  meson_version : '>=1.3.0',
  default_options : [
    'c_std=c11',
    'cpp_std=c++20',
    'warning_level=3',
  ],
)

vulkan_option = get_option('vulkan')
dx12_option = get_option('dx12')

vulkan_dependency = dependency('vulkan', required : vulkan_option)
if vulkan_option.enabled() and not vulkan_dependency.found()
  error('Vulkan support was enabled, but the Vulkan SDK or system development package was not found')
endif

if dx12_option.enabled() and host_machine.system() != 'windows'
  error('Direct3D 12 support is available only when targeting Windows; use -Ddx12=disabled')
endif

public_include = include_directories('include')

lumaweave_core = library(
  'lumaweave_core',
  'src/core/lumaweave.cpp',
  cpp_args : ['-DLW_BUILDING_LIBRARY'],
  include_directories : public_include,
  install : true,
)

install_headers(
  'include/lumaweave/lumaweave.h',
  'include/lumaweave/lumaweave.hpp',
  'include/lumaweave/version.h',
  subdir : 'lumaweave',
)

lumaweave_dependency = declare_dependency(
  include_directories : public_include,
  link_with : lumaweave_core,
)

if get_option('tests')
  subdir('tests')
endif

summary(
  {
    'Vulkan adapter' : vulkan_dependency.found(),
    'Direct3D 12 adapter' : dx12_option.enabled(),
    'Samples' : get_option('samples'),
    'Tests' : get_option('tests'),
    'Shader debug data' : get_option('shader_debug'),
    'FP16 variants' : get_option('fp16'),
    'Validation tooling' : get_option('validation'),
  },
  section : 'LumaWeave features',
  bool_yn : true,
)
