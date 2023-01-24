set(HARDEN_CXX_FLAGS_COMMON
    # cmake-format: sortable
    -pedantic-errors
    -Wall
    -Werror=cast-align
    -Werror=conversion
    -Werror=format
    -Werror=format-security
    -Werror=implicit-fallthrough
    -Werror=null-dereference
    -Werror=pedantic
    -Werror=return-type
    -Werror=sign-conversion
    -Werror=switch
    -Werror=uninitialized
    -Wextra
    -Wshadow
    -Wundef
)

set(HARDEN_CXX_FLAGS_GCC
    # cmake-format: sortable
    -Wduplicated-branches
    -Wduplicated-cond
    -Werror=arith-conversion
    -Werror=dangling-pointer=2
    -Werror=maybe-uninitialized
    -Werror=return-local-addr
    -Wformat-signedness
    -Wlogical-op
    -Wstrict-overflow=4
)
set(HARDEN_CXX_FLAGS_CLANG
    # cmake-format: sortable
    -Werror=conditional-uninitialized
    -Werror=dangling
    -Werror=delete-non-abstract-non-virtual-dtor
    -Werror=return-stack-address
    -Wfor-loop-analysis
    -Wtautological-constant-in-range-compare
)

set(INITIAL_HARDEN_CXX_FLAGS)
list(APPEND INITIAL_HARDEN_CXX_FLAGS ${HARDEN_CXX_FLAGS_COMMON}
     ${HARDEN_CXX_FLAGS_GCC} ${HARDEN_CXX_FLAGS_CLANG}
)

include(CheckCXXCompilerFlag)

set(HARDEN_CXX_FLAGS)
foreach(flag IN LISTS INITIAL_HARDEN_CXX_FLAGS)
    set(TMP_VAR_NAME "HAS_${flag}")
    string(REGEX REPLACE "[-_=]+" "_" TMP_VAR_NAME ${TMP_VAR_NAME})
    check_cxx_compiler_flag(${flag} ${TMP_VAR_NAME})
    set(HAS_FLAG ${${TMP_VAR_NAME}})
    if(HAS_FLAG)
        list(APPEND HARDEN_CXX_FLAGS ${flag})
    endif()
endforeach(flag IN LISTS INITIAL_HARDEN_CXX_FLAGS)

cmake_print_variables(HARDEN_CXX_FLAGS)
