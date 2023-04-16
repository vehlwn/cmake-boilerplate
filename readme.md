## Build

```bash
$ mkdir build && cd build
$ conan build .. --output-folder . --build=missing -s build_type=Debug
$ ninja clang-tidy
```
