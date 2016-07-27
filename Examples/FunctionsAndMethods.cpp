#include "TestReflectionModule.h"

#include "TestTypes.h"
#include "TestProperties.h"

using namespace ursine::meta;

int main(void)
{
    MetaInitialize( UsingModule( TestModule ) );

    Type soundEffectType = typeof( SoundEffect );
    Field volumeField = soundEffectType.GetField( "volume" );

    // the runtime supports overloading, but by default returns the first overload
    Method loadMethod = soundEffectType.GetMethod( "Load" );

    // creates an instance of a sound effect
    Variant effect = soundEffectType.Create( );

    // effect.volume is now 85
    volumeField.SetValue( effect, 85.0f );

    // 85 -- can also use GetValue<float>( )
    float volumeValue = volumeField.GetValue( effect ).ToFloat( );

    std::cout << "SoundEffect.volume: " << volumeValue << std::endl;

    // effect.Load is called
    loadMethod.Invoke( effect, std::string { "Explosion.wav" } );

    return 0;
}