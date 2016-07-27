#include "TestReflectionModule.h"

#include "TestTypes.h"
#include "TestProperties.h"

using namespace ursine;
using namespace meta;

int main(void)
{
    MetaInitialize( UsingModule( TestModule ) );

    return 0;
}