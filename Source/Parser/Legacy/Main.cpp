/* ----------------------------------------------------------------------------
** Copyright (c) 2016 Austin Brunkhorst, All Rights Reserved.
**
** Main.cpp
** --------------------------------------------------------------------------*/

#include "Precompiled.h"

#include "ReflectionOptions.h"
#include "ReflectionParser.h"

#include "Switches.h"

#include <chrono>
#include <fstream>

void parse(const po::variables_map &cmdLine);

int main(int argc, char *argv[])
{
    auto start = std::chrono::system_clock::now( );

    // parse command line
    try 
    {
        // path to the executable
        auto exeDir = fs::path( argv[ 0 ] ).parent_path( );

        // set the working directory to the executable directory
        if (!exeDir.empty( ))
            fs::current_path( exeDir );

        po::options_description program( "Ursine Meta Parser" );

        program.add_options( )
        ( 
            SWITCH_OPTION( Help ), 
            "Displays help information." 
        )
        ( 
            SWITCH_OPTION( TargetName ), 
            po::value<std::string>( )->required( ),
            "Input target project name." 
        )
        ( 
            SWITCH_OPTION( SourceRoot ), 
            po::value<std::string>( )->required( ),
            "Root source directory that is shared by all header files." 
        )
        ( 
            SWITCH_OPTION( InputSource ), 
            po::value<std::string>( )->required( ), 
            "Source file (header) to compile reflection data from." 
        )
            ( 
            SWITCH_OPTION( ModuleHeaderFile ), 
            po::value<std::string>( )->required( ), 
            "Header file that declares this reflection module." 
        )
        ( 
            SWITCH_OPTION( OutputModuleSource ), 
            po::value<std::string>( )->required( ), 
            "Output generated C++ module source file." 
        )
        ( 
            SWITCH_OPTION( OutputModuleFileDirectory ), 
            po::value<std::string>( )->required( ), 
            "Output directory for generated C++ module file, header/source files." 
        )
        ( 
            SWITCH_OPTION( TemplateDirectory ), 
            po::value<std::string>( )->default_value( "Templates/" ), 
            "Directory that contains the mustache templates." 
        )
        ( 
            SWITCH_OPTION( PrecompiledHeader ), 
            po::value<std::string>( ), 
            "Optional name of the precompiled header file for the project." 
        )
        (
            SWITCH_OPTION( ForceRebuild ),
            "Whether or not to ignore cache and write the header / source files."
        )
        (
            SWITCH_OPTION( DisplayDiagnostics ),
            "Whether or not to display diagnostics from clang."
        )
        ( 
            SWITCH_OPTION( CompilerIncludes ), 
            po::value<std::string>( ),
            "Optional file that includes the include directories for this target." 
        )
        (
            SWITCH_OPTION( CompilerDefines ),
            po::value<std::vector<std::string>>( )->multitoken( ),
            "Optional list of definitions to include for the compiler."
        );

        po::variables_map cmdLine;

        po::store( po::parse_command_line( argc, argv, program ), cmdLine );

        if (cmdLine.count( "help" )) 
        {
            std::cout << program << std::endl;

            return EXIT_SUCCESS;
        }

        po::notify( cmdLine );

        parse( cmdLine );
    }
    catch (std::exception &e)
    {
        utils::FatalError( e.what( ) );
    }
    catch (...) 
    {
        utils::FatalError( "Unhandled exception occurred!" );
    }

    auto duration = std::chrono::system_clock::now( ) - start;

    std::cout << "Completed in " 
              << std::chrono::duration_cast<std::chrono::milliseconds>( duration ).count( ) 
              << "ms" << std::endl;

    return EXIT_SUCCESS;
}

void parse(const po::variables_map &cmdLine)
{
    ReflectionOptions options;

    options.forceRebuild = 
        cmdLine.count( kSwitchForceRebuild ) > 0;

    options.displayDiagnostics = 
        cmdLine.count( kSwitchDisplayDiagnostics ) > 0;

    options.targetName = 
        cmdLine.at( kSwitchTargetName ).as<std::string>( );

    options.sourceRoot = 
        cmdLine.at( kSwitchSourceRoot ).as<std::string>( );

    options.inputSourceFile = 
        cmdLine.at( kSwitchInputSource ).as<std::string>( );

    options.moduleHeaderFile = 
        cmdLine.at( kSwitchModuleHeaderFile ).as<std::string>( );

    options.outputModuleSource = 
        cmdLine.at( kSwitchOutputModuleSource ).as<std::string>( );

    options.outputModuleFileDirectory = 
        cmdLine.at( kSwitchOutputModuleFileDirectory ).as<std::string>( );

    // default arguments
    options.arguments =
    { {
        "-x",
        "c++",
        "-std=c++11",
        "-D__REFLECTION_PARSER__"
    } };

    if (cmdLine.count( kSwitchPrecompiledHeader ))
    {
        options.precompiledHeader = 
            cmdLine.at( kSwitchPrecompiledHeader ).as<std::string>( );
    }
    
    if (cmdLine.count( kSwitchCompilerIncludes ))
    {
        auto includes = 
            cmdLine.at( kSwitchCompilerIncludes ).as<std::string>( );

        std::ifstream includesFile( includes );

        std::string include;

        while (std::getline( includesFile, include ))
            options.arguments.emplace_back( "-I"+ include );
    }

    if (cmdLine.count( kSwitchCompilerDefines ))
    {
        auto defines = 
            cmdLine.at( kSwitchCompilerDefines ).as<std::vector<std::string>>( );

        for (auto &define : defines)
            options.arguments.emplace_back( "-D"+ define );
    }

    options.templateDirectory = 
        cmdLine.at( kSwitchTemplateDirectory ).as<std::string>( );
    
    std::cout << std::endl;
    std::cout << "Parsing reflection data for target \"" 
              << options.targetName << "\"" 
              << std::endl;

    ReflectionParser parser( options );

    parser.Parse( );

    try
    {
        parser.GenerateFiles( );
    }
    catch (std::exception &e)
    {
        utils::FatalError( e.what( ) );
    }
}