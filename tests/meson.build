catch2_dependency = dependency(
  'catch2-with-main',
  version : '=3.15.0',
  fallback : ['catch2', 'catch2_with_main_dep'],
  default_options : ['tests=false', 'install=false'],
)

lumaweave_tests = executable(
  'lumaweave_tests',
  'unit/c_api_smoke.c',
  'unit/core_tests.cpp',
  dependencies : [catch2_dependency, lumaweave_dependency],
)
test('LumaWeave unit tests', lumaweave_tests)
