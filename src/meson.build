boost_modules = ['random', 'regex']
if get_option('use_conan')
  message('Using Conan')
  boost_deps = []
  foreach name : boost_modules
    boost_deps += dependency('boost-' + name, include_type: 'system')
  endforeach
else
  boost_deps = dependency('boost', modules: boost_modules, include_type: 'system')
endif

icu_deps = []
foreach name : [
    'icu-i18n',
    'icu-io',
    'icu-uc',
  ]
  icu_deps += dependency(name, include_type: 'system')
endforeach

random_exe = executable(
  'random',
  ['random.cpp'],
  dependencies: [boost_deps]
)

codepoints_boost_regex_exe = executable(
  'codepoints-boost-regex',
  ['codepoints-boost-regex.cpp'],
  dependencies: [boost_deps, icu_deps]
)

bench_codepoints_exe = executable(
  'bench-codepoints',
  ['bench-codepoints.cpp'],
  dependencies: [boost_deps, icu_deps]
)

icu_normalize_exe = executable(
  'icu-normalize',
  ['icu-normalize.cpp'],
  dependencies: [boost_deps, icu_deps]
)
