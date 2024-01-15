boost_modules = ['random', 'unit_test_framework']
if get_option('use_conan')
  boost_deps = []
  foreach name : boost_modules
    boost_deps += dependency('boost-' + name, include_type: 'system')
  endforeach
else
  boost_deps = dependency('boost', modules: boost_modules, include_type: 'system')
endif

test('random-dist',
  executable(
    'random-dist',
    ['random-dist.cpp'],
    dependencies: [boost_deps]
  )
)
test('random', random_exe)

str_data = '𝐀𝐁𝐂s̆ӹ'
test('codepoints-boost-regex', codepoints_boost_regex_exe, args : [str_data])
test('bench-codepoints', bench_codepoints_exe, args : ['/etc/os-release'])
test('icu-normalize', icu_normalize_exe, args : [str_data])
