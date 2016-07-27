#include "TestReflectionModule.h"

#include "TestTypes.h"
#include "TestProperties.h"

using namespace ursine::meta;

int main(void)
{
    MetaInitialize( UsingModule( TestModule ) );

    // you can also use type meta::Type::Get( "SoundEffect" ) based on a string name
    Type soundEffectType = typeof( SoundEffect );

    // the volume field in the SoundEffect struct
    Field volumeField = soundEffectType.GetField( "volume" );

    // meta data for the volume field
    const MetaManager &volumeMeta = volumeField.GetMeta( );

    // getting the "Range" property, then casting the variant as a Range
    Range &volumeRange = volumeMeta.GetProperty( typeof( Range ) ).GetValue<Range>( );

    // 0.0f
    std::cout << "SoundEffect::volume [Range.min]: " << volumeRange.min << std::endl;

    // 100.0f
    std::cout << "SoundEffect::volume [Range.max]: " << volumeRange.max << std::endl;

    // getting the "Slider" property, then casting the variant as a Slider
    Slider &volumeSlider = volumeMeta.GetProperty( typeof( Slider ) ).GetValue<Slider>( );

    // type representing the SlideType enum
    Type sliderTypeEnumType = typeof( SliderType );

    // enum representing the SliderType
    const Enum &sliderTypeEnum = sliderTypeEnumType.GetEnum( );

    // get the associative value of the enum
    std::cout << "SoundEffect::volume [Slider.type]: " << sliderTypeEnum.GetKey( volumeSlider.type ) << std::endl;

    return 0;
}