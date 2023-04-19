project(
  'Boilerplate',
  ['cpp'],
  default_options: ['cpp_std=c++17'],
  license: 'ISC',
  meson_version: '>=0.60'
)

subdir('meson')
subdir('src')

if get_option('build_testing')
  subdir('tests')
endif
