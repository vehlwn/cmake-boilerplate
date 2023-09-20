project(
  'Boilerplate',
  ['cpp'],
  default_options: ['cpp_std=c++20', 'warning_level=0'],
  license: 'ISC',
  meson_version: '>=0.60'
)

subdir('meson')
add_project_arguments(HARDEN_CXX_OPTIONS, language: 'cpp')

subdir('src')

if get_option('build_testing')
  subdir('tests')
endif
