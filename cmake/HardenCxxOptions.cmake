set(HARDEN_CXX_OPTIONS_COMMON
    # cmake-format: sortable
    -pedantic-errors
    -Wall
    -Werror=cast-align
    -Werror=conversion
    -Werror=format
    -Werror=format-nonliteral
    -Werror=implicit-fallthrough
    -Werror=parentheses
    -Werror=pedantic
    -Werror=return-type
    -Werror=sign-conversion
    -Werror=switch
    -Werror=tautological-compare
    -Werror=uninitialized
    -Wextra
    -Wnull-dereference
    -Wshadow
    -Wundef
)

set(HARDEN_CXX_OPTIONS_GCC
    # cmake-format: sortable
    -Wduplicated-branches
    -Wduplicated-cond
    -Werror=arith-conversion
    -Werror=dangling-pointer=2
    -Werror=maybe-uninitialized
    -Werror=nonnull-compare
    -Werror=return-local-addr
    -Wformat-signedness
    -Wlogical-op
    -Wstrict-overflow=4
)
set(HARDEN_CXX_OPTIONS_CLANG
    # cmake-format: sortable
    -Werror=dangling -Werror=delete-non-abstract-non-virtual-dtor
    -Werror=return-stack-address -Wfor-loop-analysis
)

set(INITIAL_HARDEN_CXX_OPTIONS)
list(APPEND INITIAL_HARDEN_CXX_OPTIONS ${HARDEN_CXX_OPTIONS_COMMON}
     ${HARDEN_CXX_OPTIONS_GCC} ${HARDEN_CXX_OPTIONS_CLANG}
)

include(CheckCXXCompilerFlag)

set(HARDEN_CXX_OPTIONS)
foreach(flag IN LISTS INITIAL_HARDEN_CXX_OPTIONS)
    set(TMP_VAR_NAME "HAS_${flag}")
    string(REGEX REPLACE "[-_=]+" "_" TMP_VAR_NAME ${TMP_VAR_NAME})
    check_cxx_compiler_flag(${flag} ${TMP_VAR_NAME})
    set(HAS_FLAG ${${TMP_VAR_NAME}})
    if(HAS_FLAG)
        list(APPEND HARDEN_CXX_OPTIONS ${flag})
    endif()
endforeach(flag IN LISTS INITIAL_HARDEN_CXX_OPTIONS)

cmake_print_variables(HARDEN_CXX_OPTIONS)
