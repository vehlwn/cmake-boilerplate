boost_dep = dependency('boost', modules: ['random', 'regex'], include_type: 'system')
icu_i18n = dependency('icu-i18n', include_type: 'system')
icu_uc = dependency('icu-uc', include_type: 'system')
icu_io = dependency('icu-io', include_type: 'system')

executable(
  'random',
  ['random.cpp'],
  dependencies: [boost_dep],
  cpp_args: HARDEN_CXX_OPTIONS
)

executable(
  'codepoints-boost-regex',
  ['codepoints-boost-regex.cpp'],
  dependencies: [boost_dep, icu_uc, icu_i18n],
  cpp_args: HARDEN_CXX_OPTIONS
)

executable(
  'bench-codepoints',
  ['bench-codepoints.cpp'],
  dependencies: [boost_dep, icu_uc, icu_i18n],
  cpp_args: HARDEN_CXX_OPTIONS
)

executable(
  'icu-normalize',
  ['icu-normalize.cpp'],
  dependencies: [boost_dep, icu_i18n, icu_io],
  cpp_args: HARDEN_CXX_OPTIONS
)
