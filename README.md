# C++ Reflection

## Preface
I set out this summer (*2015*) to implement a flexible reflection system for the game project I'm working on. This repository contains a skeleton for parts of the system that I prototyped throughout the summer. With the proper dependencies and build system setup, you should have enough to integrate into your engine / application without much fuss.

## Quick Intro
As a statically typed language, C++ wasn't designed to facilitate runtime type information. Instead, it's crazy fast and optimization friendly. As performance critical applications, it is for this reason that C++ is basically the standard backend for games.

Type introspection is crucial for complex / large code bases that need to interface with tools (*i.e. a game editor*). Unless you're a team of all programmers (*I'm sorry if that's the case*) it is effectively impossible to iterate upon a larger game without some sort of tools to abstract away code (*especially in 3D*). Without type introspection, you can expect to copy and paste a lot of boilerplate code. This is **absurdly** tedious and undesirable.

The good news is that there are *tons and tons* of great resources out there for "extending" C++ to include meta information within your code base. The most common approaches you'll find are as follows:

+ Using macros and templates to simplify the craziness that is writing the aforementioned boilerplate code.
+ Parsing your code to **generate** the crazy boilerplate code.

The latter technique isn't adopted nearly as much as the former, but feels like it's becoming much more common. With that said, I chose to use the generation technique. I'm pretty glad I did.

The purpose of this repository is to be a simple jumpstart reference for those interested in implementing the generation method in their own code base.

Here are a few links that cover more specifics on the concept (*specifically in the realm of C/C++*)

+ [GDC: Physics for Game Programmers - Debugging](http://www.gdcvault.com/play/1020065/Physics-for-Game-Programmers-Debugging) (*it's relevant, I swear!*)
+ [GDC: Robustification Through Introspection and Analysis Tools (Avoiding Developer Taxes)](http://www.gdcvault.com/play/1015586/)
+ [Game Engine Metadata Creation with Clang](http://www.myopictopics.com/?p=368)
+ [Parsing C++ in Python with Clang](http://eli.thegreenplace.net/2011/07/03/parsing-c-in-python-with-clang/)

## Goals

##### Make the pipeline as hands off as possible. 
Specifically, you shouldn't have to jump through a bunch of hoops just to expose your code to the reflection runtime library. Make changes to your code, recompile, and the changes are reflected immediately (*yep, it was intended*).

No extra button clicks or steps to synchronize the reflection data.

##### Provide rich functionality in the runtime library. 
If we're going through all this trouble in the first place, might as well make it worth while!

##### Avoid huge build times.
We're effectively compiling our code twice. First to parse our code base and understand it as intricately as a compiler does, then to *actually* compile it as per usual (*with the addition of our generated source*).

This is one of the downsides to the generation approach. Instead of manually writing these macros inline with our source, we're using the brains of a compiler. However, we would much rather sacrifice a little bit shorter build times for the luxury of cleaner, less cluttered code.

Unfortunately, this also implies creating a much less intuitive build pipeline. Don't worry though! I have some nifty diagrams for you.

## Pipeline

In our engine (_we call it **Ursine Engine**, because we're dangerously clever and played on the fact that our team name is Bear King_), we use [CMake](http://www.cmake.org/) for managing most aspects of the the overall build pipeline. CMake is a horribly wonderful tool that I've come to love despite hating it at the same time. It allows us to generate solutions for most IDEs that anyone on the team likes to use, although currently, everyone is using Visual Studio 2015 (_finally **some** C++14, baby!_). 

CMake makes this pipeline surprisingly simple which was a relief. I won't go into much specific detail, but I'll provide relevant snippets of the integration into our engine a little later when I describe the code in this repository.

Here's a diagram of the entire pipeline from writing the source, to building your game / application.

![Pipeline Diagram](http://imgur.com/V7RLPAj.png "Pipeline Diagram")

## Code

The respository has two parts - [Parser](https://github.com/AustinBrunkhorst/CPP-Reflection/tree/master/Source/Parser) and [Runtime](https://github.com/AustinBrunkhorst/CPP-Reflection/tree/master/Source/Runtime). 

+ **Parser** is for the command line source parsing tool. (_requires [Boost 1.59.0](http://www.boost.org/users/history/version_1_59_0.html) and [libclang 3.7.0](http://llvm.org/releases/download.html)_)
+ **Runtime** is for the reflection runtime library.

### CMake Prebuild Example

This is basic example of adding the prebuild step to an existing target in CMake.

**Note:** this assumes you have created empty files for `${META_GENERATED_HEADER}` and `${META_GENERATED_SOURCE}` and added it to the list of sources when calling `add_executable( )`. Otherwise, CMake will complain about the files not existing initially.

```CMake
# assume a target has been created, with add_executable( ... )
set(PROJECT_NAME "Example")

# path to the reflection parser executable
set(PARSE_TOOL_EXE "ReflectionParser.exe")

# input source file to pass to the reflection parser compiler
# in this file, include any files that you want exposed to the parser
set(PROJECT_META_HEADER "Reflection.h")

# generated file names
set(META_GENERATED_HEADER "Meta.Generated.h")
set(META_GENERATED_SOURCE "Meta.Generated.cpp")

# fetch all include directories for the project target
get_property(DIRECTORIES TARGET ${PROJECT_NAME} PROPERTY INCLUDE_DIRECTORIES)

# flags that will eventually be based to the reflection parser compiler
set(META_FLAGS "")

# build the include directory flags
foreach (DIRECTORY ${DIRECTORIES})
    set(META_FLAGS ${meta_flags} "\\-I${DIRECTORY}")
endforeach ()

# include the system directories
if (MSVC)
    # assume ${VS_VERSION} is the version of Visual Studio being used to compile
    set(META_FLAGS ${META_FLAGS} 
        "\\-IC:/Program Files (x86)/Microsoft Visual Studio ${VS_VERSION}/VC/include"
    )
else ()
    # you can figure it out for other compilers :)
    message(FATAL_ERROR "System include directories not implemented for this compiler.")
endif ()

# add the prebuild command that invokes the reflection parser executable
add_custom_command(
    TARGET ${PROJECT_NAME}
    PRE_BUILD
    COMMAND call "${PARSE_TOOL_EXE}"
    --target-name "${PROJECT_NAME}"
    --in-source "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_SOURCE_DIR}/${PROJECT_META_HEADER}"
    --out-header "${META_GENERATED_HEADER}"
    --out-source "${META_GENERATED_SOURCE}"
    --flags ${META_FLAGS}
)
```

### String Templates
Generating code is usually a pretty ugly process. 

Instead of writing the characters manually (i.e. `output += "REGISTER_FUNCTION(" + name + ")"`), I wanted to use *"String Templates"*. That is why I chose [Mustache](https://mustache.github.io/). I found a simple [header only implemenation](https://github.com/kainjow/Mustache), which is included in the [Parser](https://github.com/AustinBrunkhorst/CPP-Reflection/blob/master/Source/Parser/Mustache.h) section.

In the **Generate Source Files** section of the pipeline diagram, you'll notice two steps. *"Compile"* and *"Render"*. Compile simply takes all of the types that we've extracted and [compiles the data to be referenced in Mustache](https://github.com/AustinBrunkhorst/CPP-Reflection/blob/master/Source/Parser/ReflectionParser.cpp#L217-L220). Render actually renders the templates and writes them to the configured output files.

In the [Templates](https://github.com/AustinBrunkhorst/CPP-Reflection/tree/master/Templates) folder of the repository, you'll find the mustache template files referenced in the reflection parser.

### Type Meta Data
One of the biggest features that I wanted to implement in the runtime library is being able to add meta data to types at compile time.

If you've ever used C#, you know they have a pretty groovy reflection system built into the language. I really like their syntax for [Attributes](http://www.tutorialspoint.com/csharp/csharp_attributes.htm), which is a way to add meta data to language types / constructs.

The closest I could get to this style, was with the use of Macros. C++11 introduced [Attribute Specifiers](http://en.cppreference.com/w/cpp/language/attributes) as a way to hint compilers on intended behavior or add language extensions. Unfortunately, compiler support varies widely, and as mentioned it's only managed at compile time.

Luckily for us, Clang supports the attribute `annotate( )`. You can extract the contents of an annotation with [libclang](https://github.com/AustinBrunkhorst/CPP-Reflection/blob/master/Source/Parser/MetaDataManager.cpp#L10-L17).

The syntax for this attribute look something like this.

    __attribute__(( annotate( "Hey look at this annotation!" ) ))
    
You might be thinking, *"But it's only for Clang.. how will this work in MSVC?"* 

More good news! libclang preprocesses source files, so we can use preprocessor directives. In the source parsing tool, I define `__REFLECTION_PARSER__` [before compiling](https://github.com/AustinBrunkhorst/CPP-Reflection/blob/master/Source/Parser/Main.cpp#L126). We can use this to make a nice solution for all compilers.

```C++
#if defined(__REFLECTION_PARSER__)
#   define Meta(...) __attribute__((annotate(#__VA_ARGS__)))
#else
#   define Meta(...)
#endif
```

We would use it like so.

```C++
Meta(Mashed)
int potatoes;
```
    
Now that I could annotate code, I needed to define how I would interact with it. Initially I assumed key value pairs separated by commas, like so.

```C++
Meta(Key = Value, Key2, Key = "Yep!")
```

But after reviewing this approach with my teammate [Jordan](http://www.jordanellis.me), he came up with the brilliant idea of doing exactly what C# does, and that is using user defined types as annotations, queryable at runtime. So I came up with this.

```C++
struct Mashed : public MetaProperty { };

Meta(Mashed)
int potatoes;
```

Heres how it works - I treat all values delimited by commas as constructors. If a value doesn't have parenthases, it's assumed to be a default constructor. 

For each constructor, I then extract the arguments provided. When I generate the source, I simply paste the extracted arguments as a constructor call of the provided type. The value is converted to a `Variant` and accessible at runtime. This allows us to do some really awesome things.

```C++
enum class SliderType 
{
    Horizontal,
    Vertical
};

struct Slider : public MetaProperty 
{
    SliderType type;
    
    Slider(SliderType type) 
        : type( type ) { }
};

struct Range : public MetaProperty 
{
    float min, max;
    
    Range(float min, float max) 
        : min( min )
        , max( max ) { }
};

Meta(Range(0.0f, 1.0f), Slider(SliderType::Horizontal))
float someIntensityField;
```

One of the coolest things about this aside from type safety, is that Visual Studio correctly syntax highlights the contents of the macro and also provides intellisense! It's a beautiful thing. Here's a more complete example of interfacing with it at runtime using the runtime library.

```C++
struct SoundEffect 
{
    Meta(Range(0.0f, 100.0f))
    float volume;
};

int main(void)
{
    // you can also use type meta::Type::Get( "SoundEffect" ) based on a string name
    Field volumeField = typeof( SoundEffect ).GetField( "volume" );
    
    // meta data for the volume field
    MetaManager &volumeMeta = soundEffectType.GetMeta( );
    
    // getting the "Range" property, then casting the variant as a range
    Variant volumeRange = volumeMeta.GetProperty( typeof( Range ) ).GetValue<Range>( );
    
    // 0.0f
    float min = volumeRange.min;
    
    // 100.0f
    float max = volumeRange.max;
    
    return 0;
}
```

### Function Binding

Another notoriously difficult or convoluted process in managing reflection info in C++ is dynamically invoking functions / methods. 

The most common approach is to store raw function / method pointers and calculate the offsets of arguments. The result is a ton of templates and difficult to follow operations. Not to mention, I can't imagine it's fun to debug!

In libclang, you're able to easily extract signatures from functions. With this in mind, I came up with the most simple approach that I could think of. **Wrapping function calls in generated lambdas**.

Here's a simple demonstration of the concept.

```C++
int foo(int a, float b, double c) 
{ 
    return 0;
}

auto fooWrapper = [](int a, float b, double c) 
{
    return foo( a, b, c );
};

// same behavior as foo( 0, 1.0f, 2.0 );
fooWrapper( 0, 1.0f, 2.0 );
```

In the context of our runtime library, here's an example of something that might be generated for a class method.

```C++
class DemoClass 
{
public:
    int someMethod(int a)
    {
        return a;
    }
};

auto someMethodWrapper = [](Variant &obj, ArgumentList &args)
{ 
    auto &instance = obj.GetValue<DemoClass>( );
    
    return Variant {
        instance.someMethod(
            args[ 0 ].GetValue<int>( )
        )
    };
};
```

That's it! It's much less compilicated than the previously mentioned approach. This concept is also applied to fields / globals - getters and setters are simply generated lambdas.

There are some downsides though:
+ Larger code size. For each generated lambda, the compiler has to generate a bunch of symbols behind the scenes.
+ Larger compile times.
+ Decent amount of indirection just for one function call.

You shouldn't have to worry **too** much however. If like most people, you use reflection for editor functionality, not a physics simulation. Performance in most cases is not critical.

Here's a more complete example of dynamically calling functions with the runtime library.

```C++
struct SoundEffect 
{
    float volume;

    void Load(const char *filename);
};

int main(void)
{
	Type soundEffectType = typeof( SoundEffect );
	auto volumeField = soundEffectType.GetField( "volume" );

	// the runtime supports overloading, but by default returns the first overload
	Method loadMethod = soundEffectType.GetMethod( "Load" );

	// creates an instance of a sound effect
	Variant effect = soundEffectType.Create( );

	// effect.volume is now 85
	volumeField.SetValue( effect, 85.0f );

	// 85
	volumeField.GetValue( effect );

	// effect.Load is called
	loadMethod.Invoke( effect, { "Explosion.wav" } );

	return 0;
}
```