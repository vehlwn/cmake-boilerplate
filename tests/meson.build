boost_modules = ['random', 'unit_test_framework']
if get_option('use_conan')
  boost_deps = []
  foreach name : boost_modules
    boost_deps += dependency('boost-' + name, include_type: 'system')
  endforeach
else
  boost_deps = dependency('boost', modules: boost_modules, include_type: 'system')
endif

test('random',
  executable(
    'random',
    ['random.cpp'],
    dependencies: [boost_deps],
    cpp_args: HARDEN_CXX_OPTIONS
  )
)
