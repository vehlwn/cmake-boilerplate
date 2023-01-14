set(HARDEN_CXX_FLAGS_COMMON
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
    -Wlogical-op
    -Wshadow
    -Wundef
    -pedantic-errors
)

set(HARDEN_CXX_FLAGS_GCC
    -Wduplicated-branches
    -Wduplicated-cond
    -Werror=arith-conversion
    -Werror=maybe-uninitialized
    -Werror=return-local-addr
    -Wformat-signedness
    -Wstrict-overflow=4
)
set(HARDEN_CXX_FLAGS_CLANG
    -Werror=conditional-uninitialized -Werror=delete-non-abstract-non-virtual-dtor
    -Werror=return-stack-address -Wfor-loop-analysis
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

message(STATUS "HARDEN_CXX_FLAGS=${HARDEN_CXX_FLAGS}")
