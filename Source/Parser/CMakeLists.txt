cmake_minimum_required(VERSION 2.8.3)

project(MetaParser CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../CMake")

include(Precompiled)

set(HEADER_FILES
    Cursor.h
    CursorType.h
    MetaDataConfig.h
    MetaDataManager.h
    MetaUtils.h
    MetaUtils.hpp
    Namespace.h
    Precompiled.h
    ReflectionOptions.h
    ReflectionParser.h
    ReservedTypes.h
    Switches.h
    Templates.h
    Version.h
    LanguageTypes/Class.h
    LanguageTypes/Constructor.h
    LanguageTypes/Enum.h
    LanguageTypes/External.h
    LanguageTypes/Field.h
    LanguageTypes/Function.h
    LanguageTypes/Global.h
    LanguageTypes/Invokable.h
    LanguageTypes/LanguageType.h
    LanguageTypes/Method.h
    Module/ModuleFile.h
    Tokenizer/TokenizerResult.h
    Tokenizer/TokenizerState.h
    Tokenizer/TokenType.h
    Tokenizer/Token.h
    Tokenizer/Tokenizer.h
    Tokenizer/ConstructorTokenSymbols.inl
    Tokenizer/Impl/TokenizerResult.hpp
    Tokenizer/Impl/TokenizerState.hpp
    Tokenizer/Impl/Token.hpp
    Tokenizer/Impl/Tokenizer.hpp
)

set(SOURCE_FILES
    Cursor.cpp
    CursorType.cpp
    Main.cpp
    MetaDataManager.cpp
    MetaUtils.cpp
    Precompiled.cpp
    ReflectionParser.cpp
    LanguageTypes/Class.cpp
    LanguageTypes/Constructor.cpp
    LanguageTypes/Enum.cpp
    LanguageTypes/External.cpp
    LanguageTypes/Field.cpp
    LanguageTypes/Function.cpp
    LanguageTypes/Global.cpp
    LanguageTypes/Invokable.cpp
    LanguageTypes/LanguageType.cpp
    LanguageTypes/Method.cpp
)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_ALL_NO_LIB ON)

# disable auto-linking
add_definitions(-DBOOST_ALL_NO_LIB)

find_package(Boost 1.59.0 REQUIRED 
    COMPONENTS 
    system
    filesystem
    program_options
    regex
)

# add boost includes
include_directories(${Boost_INCLUDE_DIRS})

find_package(LLVM REQUIRED)

# add LLVM includes
include_directories(${LLVM_INCLUDE_DIRS})

# allow use of Common and Library directories
include_directories(.)
include_directories(..)
include_directories(../Common)
include_directories(../Common/Lib)

# header files are superflous, but some IDEs (Visual Studio) don't include
# them in the solution explorer without them being added to the list of sources
add_executable(MetaParser ${HEADER_FILES} ${SOURCE_FILES})

link_directories(${LLVM_LIBRARY_DIR})

# statically link with Boost & LibClang
target_link_libraries(MetaParser ${Boost_LIBRARIES} ${LIBCLANG_LIBRARY})

set_precompiled_header(MetaParser Precompiled.h Precompiled.cpp)

if (MSVC)
    # disable security warnings
    add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)

    target_compile_options(MetaRuntime 
        PUBLIC
        # treat warnings as errors
        /WX 
        # multi process compilation
        /MP
    )

    # detect version of Visual Studio
    if (MSVC10)
        set(VS_VERSION "10")
    elseif (MSVC11)
        set(VS_VERSION "11")
    elseif (MSVC12)
        set(VS_VERSION "12")
    elseif (MSVC14)
        set(VS_VERSION "14")
    endif()

    # cmake is gross sometimes
    set(_PROGRAM_FILES_x86 "ProgramFiles(x86)")
    set(PROGRAM_FILES_x86 "$ENV{${_PROGRAM_FILES_x86}}")
    set(SYSTEM_INCLUDES "${PROGRAM_FILES_x86}/Microsoft Visual Studio ${VS_VERSION}.0/VC/include")

    # normalize slashes
    string(REPLACE "\\" "/" SYSTEM_INCLUDES "${SYSTEM_INCLUDES}")
else ()
    target_compile_options(MetaParser
        PUBLIC -std=c++11
    )

    set(SYSTEM_INCLUDES "/usr/include/c++/${CMAKE_CXX_COMPILER_VERSION}")
endif ()

if (SYSTEM_INCLUDES)
    # visual studio seems to have issues with escape characters in post build commands
    set_property(TARGET MetaParser APPEND PROPERTY COMPILE_DEFINITIONS SYSTEM_INCLUDE_DIRECTORY="${SYSTEM_INCLUDES}")
else ()
    message(FATAL_ERROR "System include directories not implemented for this compiler.")
endif ()

# copy resources on post build
add_custom_command(TARGET MetaParser POST_BUILD
    # mustache templates directory
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_LIST_DIR}/../../Resources"
        $<TARGET_FILE_DIR:MetaParser>
    # LibClang shared library
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${LIBCLANG_SHARED_LIBRARY}
        $<TARGET_FILE_DIR:MetaParser>
)
