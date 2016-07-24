cmake_minimum_required(VERSION 2.8)

project(MetaParser CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../CMake")

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

# statically link with Boost & LibClang
target_link_libraries(MetaParser ${Boost_LIBRARIES} ${LLVM_LIBCLANG_LIBRARY})

if (MSVC)
	# disable MSVC security warnings
	add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
endif ()

# copy shared libraries on post build
add_custom_command(TARGET MetaParser POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${LLVM_LIBCLANG_SHARED_LIBRARY}
		$<TARGET_FILE_DIR:MetaParser>
)