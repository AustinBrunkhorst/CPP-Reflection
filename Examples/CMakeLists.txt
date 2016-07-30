cmake_minimum_required(VERSION 2.8.3)

project(MetaTests CXX)

add_subdirectory(../Source/Runtime MetaRuntime)
add_subdirectory(../Source/Parser MetaParser)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../Source/CMake")

include(MetaParser)

include_directories(${META_RUNTIME_INCLUDE_DIRS})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

set(TEST_META_SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}")
set(TEST_META_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/Generated")

set(TEST_META_GENERATED_HEADERS "")
set(TEST_META_GENERATED_SOURCES "")

set(TEST_REFLECTION_HEADER TestReflection.h)
set(TEST_MODULE_HEADER TestReflectionModule.h)
set(TEST_MODULE_TARGET TestModule)

set(TEST_HEADERS TestProperties.h TestTypes.h)

meta_parser_prebuild(
    TARGET ${TEST_MODULE_TARGET}
    GENERATED_DIR ${TEST_META_GENERATED_DIR}
    SOURCE_ROOT ${TEST_META_SOURCE_ROOT}
    HEADER_FILES ${TEST_HEADERS}
    MODULE_HEADER ${TEST_MODULE_HEADER}
    OUT_MODULE_SOURCE META_MODULE_SOURCE
    OUT_GENERATED_FILES META_GENERATED_FILES
    OUT_INC TEST_META_GENERATED_HEADERS
    OUT_SRC TEST_META_GENERATED_SOURCES
)

add_library(${TEST_MODULE_TARGET} ${META_GENERATED_FILES})

target_link_libraries(${TEST_MODULE_TARGET} MetaRuntime)

if (MSVC)
	add_compile_options(
		# treat warnings as errors
		/WX
		# multi process compilation
		/MP
	)
else ()
	add_compile_options(
		-std=c++11
	)
endif ()

macro (add_meta_test TARGET SOURCES)
	add_executable(${TARGET} 
		${TEST_HEADERS} 
		${TEST_META_GENERATED_HEADERS} 
		${TEST_META_GENERATED_SOURCES} 
		${SOURCES}
	)

	target_link_libraries(${TARGET} MetaRuntime ${TEST_MODULE_TARGET})
	set_property(TARGET ${TARGET} PROPERTY FOLDER Tests)
endmacro ()

add_meta_test(MetaProperties MetaProperties.cpp)
add_meta_test(Enums Enums.cpp)
add_meta_test(FunctionsAndMethods FunctionsAndMethods.cpp)
add_meta_test(Arrays Arrays.cpp)
add_meta_test(Serialization Serialization.cpp)

meta_parser_build(
    TARGET ${TEST_MODULE_TARGET}
    SOURCE_ROOT ${TEST_META_SOURCE_ROOT}
    GENERATED_DIR ${TEST_META_GENERATED_DIR}
    GENERATED_FILES ${META_GENERATED_FILES}
    SOURCE_FILE ${TEST_REFLECTION_HEADER}
    MODULE_HEADER ${TEST_MODULE_HEADER}
    MODULE_SOURCE_FILE ${META_MODULE_SOURCE}
    HEADER_FILES ${TEST_HEADERS}
    PARSER_EXECUTABLE "$<TARGET_FILE:MetaParser>"
)
