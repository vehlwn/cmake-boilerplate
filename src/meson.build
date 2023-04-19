icu_deps = []
if get_option('use_conan')
  message('Using Conan')
  boost_deps = []
  foreach name : [
      'boost-random',
      'boost-regex',
    ]
    boost_deps += dependency(name, include_type: 'system')
  endforeach
else
  boost_deps = dependency('boost', modules: ['random', 'regex'], include_type: 'system')
endif

foreach name : [
    'icu-i18n',
    'icu-io',
    'icu-uc',
  ]
  icu_deps += dependency(name, include_type: 'system')
endforeach

executable(
  'random',
  ['random.cpp'],
  dependencies: [boost_deps]
)

executable(
  'codepoints-boost-regex',
  ['codepoints-boost-regex.cpp'],
  dependencies: [boost_deps, icu_deps]
)

executable(
  'bench-codepoints',
  ['bench-codepoints.cpp'],
  dependencies: [boost_deps, icu_deps]
)

executable(
  'icu-normalize',
  ['icu-normalize.cpp'],
  dependencies: [boost_deps, icu_deps]
)
