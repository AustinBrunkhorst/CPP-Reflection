set(LLVM_SEARCH_PATHS
    ${LLVM_ROOT}
    $ENV{LLVM_ROOT}
)

set(LIBCLANG_LIBRARY_NAME 
    "libclang${CMAKE_STATIC_LIBRARY_SUFFIX}"
)

set(LIBCLANG_SHARED_LIBRARY_NAME 
    "libclang${CMAKE_SHARED_LIBRARY_SUFFIX}"
)

# include directories
find_path(LLVM_INCLUDE_DIRS
    NAMES "clang-c/Index.h"
    PATHS ${LLVM_SEARCH_PATHS}
    PATH_SUFFIXES "include"
)

# static library directory
find_path(LLVM_LIBRARY_DIR
    NAMES ${LIBCLANG_LIBRARY_NAME}
    PATHS ${LLVM_SEARCH_PATHS}
    PATH_SUFFIXES "lib"
)

# shared library directory
find_path(LLVM_BINARY_DIR
    NAMES ${LIBCLANG_SHARED_LIBRARY_NAME}
    PATHS ${LLVM_SEARCH_PATHS}
    PATH_SUFFIXES "bin"
)

# unable to find everything
if (NOT LLVM_INCLUDE_DIRS OR 
    NOT LLVM_LIBRARY_DIR OR
    NOT LLVM_BINARY_DIR)
    message(SEND_ERROR 
        "Unable to find LLVM installation. "
        "Make sure that \"LLVM_ROOT\" is set with the installation directory in either an environment variable or through the CMake GUI."
    )
endif ()

set(LLVM_LIBCLANG_LIBRARY 
    "${LLVM_LIBRARY_DIR}/${LIBCLANG_LIBRARY_NAME}"
)

set(LLVM_LIBCLANG_SHARED_LIBRARY 
    "${LLVM_BINARY_DIR}/${LIBCLANG_SHARED_LIBRARY_NAME}"
)