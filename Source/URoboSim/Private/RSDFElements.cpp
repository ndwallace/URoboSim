#include "RSDFElements.h"

bool FSDFElement::IsRequired()
{
    return bRequired;
}

// FString FSDFElement::GetType()
// {
//     return Type;
// }

FString FSDFElement::GetDescription()
{
    return Description;
}

// FSDFFloatElement::FSDFFloatElement()
// {
//     Type = "double";
// }
// FSDFBoolElement::FSDFBoolElement()
// {
//     Type = "bool";
// }
// FSDFStringElement::FSDFStringElement()
// {
//     Type = "string";
// }
FSDFPose::FSDFPose()
{
    bRequired = false;
    Description = "";
}
FSDFIXX::FSDFIXX()
{
    bRequired = true;
    Description = "";
}
FSDFIXY::FSDFIXY()
{
    bRequired = false;
    Description = "";
}
FSDFIXZ::FSDFIXZ()
{
    bRequired = false;
    Description = "";
}
FSDFIYY::FSDFIYY()
{
    bRequired = false;
    Description = "";
}
FSDFIYZ::FSDFIYZ()
{
    bRequired = false;
    Description = "";
}
FSDFIZZ::FSDFIZZ()
{
    bRequired = false;
    Description = "";
}
FSDFVoltage::FSDFVoltage()
{
    bRequired = false;
    Description = "";
}
FSDFLoop::FSDFLoop()
{
    bRequired = false;
    Description = "";
}
FSDFContact::FSDFContact()
{
    bRequired = false;
    Description = "";
}
FSDFGain::FSDFGain()
{
    bRequired = false;
    Description = "";
}
FSDFPitch::FSDFPitch()
{
    bRequired = false;
    Description = "";
}
FSDFUri::FSDFUri()
{
    bRequired = false;
    Description = "";
}
FSDFPlugin::FSDFPlugin()
{
    bRequired = false;
    Description = "";
}
FSDFFarClip::FSDFFarClip()
{
    bRequired = false;
    Description = "";
}
FSDFNearClip::FSDFNearClip()
{
    bRequired = false;
    Description = "";
}
FSDFFov::FSDFFov()
{
    bRequired = false;
    Description = "";
}
FSDFTexture::FSDFTexture()
{
    bRequired = false;
    Description = "";
}
FSDFMass::FSDFMass()
{
    bRequired = false;
    Description = "";
}
FSDFInertia::FSDFInertia()
{
    bRequired = false;
    Description = "";
}
FSDFAngular::FSDFAngular()
{
    bRequired = false;
    Description = "";
}
FSDFLinear::FSDFLinear()
{
    bRequired = false;
    Description = "";
}
FSDFGravity::FSDFGravity()
{
    bRequired = false;
    Description = "";
}
FSDFEnableWind::FSDFEnableWind()
{
    bRequired = false;
    Description = "";
}
FSDFSelfColide::FSDFSelfColide()
{
    bRequired = false;
    Description = "";
}
FSDFKinematic::FSDFKinematic()
{
    bRequired = false;
    Description = "";
}
FSDFMustBeBaseLink::FSDFMustBeBaseLink()
{
    bRequired = false;
    Description = "";
}
FSDFVelocityDecay::FSDFVelocityDecay()
{
    bRequired = false;
    Description = "";
}
FSDFFrame::FSDFFrame()
{
    bRequired = false;
    Description = "";
}
FSDFInertial::FSDFInertial()
{
    bRequired = false;
    Description = "";
}
FSDFCollision::FSDFCollision()
{
    bRequired = false;
    Description = "";
}
FSDFVisual::FSDFVisual()
{
    bRequired = false;
    Description = "";
}
FSDFSensor::FSDFSensor()
{
    bRequired = false;
    Description = "";
}
FSDFProjector::FSDFProjector()
{
    bRequired = false;
    Description = "";
}
FSDFAudioSink::FSDFAudioSink()
{
    bRequired = false;
    Description = "";
}
FSDFAudioSource::FSDFAudioSource()
{
    bRequired = false;
    Description = "";
}
FSDFBattery::FSDFBattery()
{
    bRequired = false;
    Description = "";
}
