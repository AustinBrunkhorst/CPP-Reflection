#include "TestReflectionModule.h"

#include "TestTypes.h"
#include "TestProperties.h"

using namespace ursine;
using namespace meta;

int main(void)
{
    MetaInitialize( UsingModule( TestModule ) );

    Array<int> intArray { 1, 2, 3, 4, 5 };

    Variant intArrayVariant = intArray;

    ArrayWrapper arrayWrapper = intArrayVariant.GetArray( );

    // updating a value
    arrayWrapper.SetValue( 0, 1000 );

    // inserting a value
    arrayWrapper.Insert( 0, -100 );

    // removing a value
    arrayWrapper.Remove( 5 );

    size_t size = arrayWrapper.Size( );
    
    std::cout << "values: ";

    for (size_t i = 0; i < size; ++i)
    {
        // could also use .GetValue<int>( )
        std::cout << arrayWrapper.GetValue( i ).ToInt( ) << " ";
    }

    return 0;
}