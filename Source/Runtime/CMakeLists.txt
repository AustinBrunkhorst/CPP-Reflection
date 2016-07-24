cmake_minimum_required(VERSION 2.8)

project(MetaRuntime CXX)

set(HEADER_FILES
	VariantPolicy.h
	Argument.h
	ArgumentConfig.h
	ArrayConfig.h
	ArrayVariantContainer.h
	ArrayWrapper.h
	ArrayWrapperBase.h
	ArrayWrapperContainer.h
	Constructor.h
	ConstructorInvoker.h
	ConstructorInvokerBase.h
	Destructor.h
	DestructorInvoker.h
	DestructorInvokerBase.h
	Enum.h
	EnumBase.h
	EnumContainer.h
	Field.h
	FieldGetter.h
	FieldGetterBase.h
	FieldSetter.h
	FieldSetterBase.h
	Function.h
	FunctionInvoker.h
	FunctionInvokerBase.h
	Global.h
	GlobalGetter.h
	GlobalGetterBase.h
	GlobalSetter.h
	GlobalSetterBase.h
	Invokable.h
	InvokableConfig.h
	Macros.h
	Meta.h
	MetaContainer.h
	MetaManager.h
	MetaProperty.h
	MetaTraits.h
	Method.h
	MethodInvoker.h
	MethodInvokerBase.h
	Object.h
	ObjectWrapper.h
	Precompiled.h
	ReflectionDatabase.h
	ReflectionModule.h
    RuntimeMetaProperties.h
	Type.h
	TypeConfig.h
	TypeData.h
	TypeInfo.h
	Variant.h
	VariantBase.h
	VariantContainer.h
    Impl/EnumContainer.hpp
    Impl/Field.hpp
    Impl/FieldGetter.hpp
    Impl/FieldSetter.hpp
    Impl/Function.hpp
    Impl/FunctionInvoker.hpp
    Impl/GlobalGetter.hpp
    Impl/GlobalSetter.hpp
    Impl/Invokable.hpp
    Impl/MetaManager.hpp
    Impl/MetaProperty.hpp
    Impl/Method.hpp
    Impl/MethodInvoker.hpp
    Impl/ReflectionDatabase.hpp
    Impl/Type.hpp
    Impl/TypeData.hpp
    Impl/TypeInfo.hpp
    Impl/TypeUnpacker.hpp
    Impl/Variant.hpp
    Impl/VariantContainer.hpp
    Impl/VariantContainerStandardTypes.hpp
    Impl/VoidFunctionInvoker.hpp
    Impl/VoidMethodInvoker.hpp
    Impl/Argument.hpp
    Impl/ArrayVariantContainer.hpp
    Impl/ArrayWrapper.hpp
    Impl/ArrayWrapperContainer.hpp
    Impl/Constructor.hpp
    Impl/ConstructorInvoker.hpp
    Impl/Destructor.hpp
    Impl/DestructorInvoker.hpp
)

set(SOURCE_FILES
	VariantContainer.cpp
	Argument.cpp
	ArrayWrapper.cpp
	Constructor.cpp
	Destructor.cpp
	Enum.cpp
	EnumBase.cpp
	Field.cpp
	Function.cpp
	Global.cpp
	Invokable.cpp
	MetaContainer.cpp
	MetaManager.cpp
	Method.cpp
	ObjectWrapper.cpp
	Precompiled.cpp
	ReflectionDatabase.cpp
	ReflectionModule.cpp
	Type.cpp
	TypeData.cpp
	Variant.cpp
	VariantBase.cpp
)

# allow use of Common and Library directories
include_directories(..)
include_directories(../Common)
include_directories(../Common/Lib)

# header files are superflous, but some IDEs (Visual Studio) don't include
# them in the solution explorer without them being added to the list of sources
add_library(MetaRuntime STATIC 
    ${HEADER_FILES} 
    ${SOURCE_FILES}

    # compile the JSON library
    ../Common/Lib/json11.cpp
)