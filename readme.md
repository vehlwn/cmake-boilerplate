## Build

```bash
$ mkdir build && cd build
$ conan build .. --output-folder . --build=missing -s build_type=Debug
$ ninja clang-tidy
$ meson configure -D build_testing=true
$ meson test

# Alternative with conan:
$ conan build .. --output-folder . --build=missing -s build_type=Debug --profile ../clang-profile.ini
```
