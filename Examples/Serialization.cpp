#include "TestReflectionModule.h"

#include "TestTypes.h"
#include "TestProperties.h"

using namespace ursine;
using namespace meta;

int main(void)
{
    MetaInitialize( UsingModule( TestModule ) );

    ///////////////////////////////////////////////////////////////////////////
    // Serialization
    ///////////////////////////////////////////////////////////////////////////

    ComplexType complexType;

    complexType.stringValue = "Testing";
    complexType.intValue = 23;
    complexType.floatValue = 77.0f;
    complexType.doubleValue = 86.35f;

    complexType.soundEffect.volume = 50.0f;

    complexType.arrayValue = { 1, 2, 3, 4, 5 };

    complexType.enumValue = Eighty;

    std::cout << "Serialized: " 
              << Variant( complexType ).SerializeJson( ).dump( ) 
              << std::endl;

    ///////////////////////////////////////////////////////////////////////////
    // Deserialization
    ///////////////////////////////////////////////////////////////////////////

    std::string complexJson = R"(
        {
            "arrayValue": [ 5, 6, 7, 8 ],
            "doubleValue": 100.0,
            "enumValue": "Two",
            "floatValue": 98.5,
            "intValue": -25,
            "soundEffect":{
                "volume": 100.0
            },
            "stringValue": "Deserialization!"
        }
    )";

    std::string jsonError;

    // This is a static helper method. It is essentially doing this -
    // typeof( ComplexType ).DeserializeJson( ).GetValue<ComplexType>( )
    ComplexType deserializedComplexType = Type::DeserializeJson<ComplexType>( 
        Json::parse( complexJson, jsonError )
    );

    std::cout << "Deserialized: " << std::endl
              << Variant( deserializedComplexType ).SerializeJson( ).dump( )
              << std::endl;

    return 0;
}