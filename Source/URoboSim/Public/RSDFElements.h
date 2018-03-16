#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RSDFElements.generated.h"


USTRUCT()
struct UROBOSIM_API FSDFElement
{
    GENERATED_BODY()
public:
    bool IsRequired();
    // FString GetType();
    FString GetDescription();

    // virtual void SetToDefault(){};
protected:
    bool bRequired;
    // FString Type;
    FString Description;
};


USTRUCT()
struct UROBOSIM_API FSDFFloatElement : public FSDFElement
{
    GENERATED_BODY()
public:
    // FSDFFloatElement();
    float Value;

    bool operator== (const float &FloatValue)
    {
        return Value==FloatValue;
    }
};

USTRUCT()
struct UROBOSIM_API FSDFBoolElement : public FSDFElement
{
    GENERATED_BODY()
public:
    // FSDFBoolElement();
    bool Value;

    bool operator== (const bool &BoolValue)
    {
        return Value==BoolValue;
    }
};

USTRUCT()
struct UROBOSIM_API FSDFStringElement : public FSDFElement
{
    GENERATED_BODY()
public:
    // FSDFStringElement();
    FString Value;

    bool operator== (const FString &StringValue)
    {
        return Value.Equals(StringValue);
    }
};

USTRUCT()
struct UROBOSIM_API FSDFPoseElement : public FSDFElement
{
    GENERATED_BODY()
public:
    FTransform Value;

    bool operator== (const FTransform &TransformValue)
    {
        return Value.Equals(TransformValue);
    }
};

USTRUCT()
struct UROBOSIM_API FSDFPose : public FSDFPoseElement
{
    GENERATED_BODY()
public:
    FSDFPose();
    FString Frame;
};

USTRUCT()
struct UROBOSIM_API FSDFIXX : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFIXX();
};

USTRUCT()
struct UROBOSIM_API FSDFIXY : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFIXY();
};

USTRUCT()
struct UROBOSIM_API FSDFIXZ : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFIXZ();
};

USTRUCT()
struct UROBOSIM_API FSDFIYY : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFIYY();
};

USTRUCT()
struct UROBOSIM_API FSDFIYZ : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFIYZ();
};

USTRUCT()
struct UROBOSIM_API FSDFIZZ : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFIZZ();
};

USTRUCT()
struct UROBOSIM_API FSDFVoltage : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFVoltage();

};

USTRUCT()
struct UROBOSIM_API FSDFLoop : public FSDFBoolElement
{
    GENERATED_BODY()
public:
    FSDFLoop();
};

USTRUCT()
struct UROBOSIM_API FSDFContact : public FSDFElement
{
    GENERATED_BODY()
public:
    FSDFContact();
    FString Collision;
};

USTRUCT()
struct UROBOSIM_API FSDFGain : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFGain();
};

USTRUCT()
struct UROBOSIM_API FSDFPitch : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFPitch();
};

USTRUCT()
struct UROBOSIM_API FSDFUri : public FSDFStringElement
{
    GENERATED_BODY()
public:
    FSDFUri();
};

USTRUCT()
struct UROBOSIM_API FSDFPlugin : public FSDFElement
{
    GENERATED_BODY()
public:
    FSDFPlugin();
    FString Name;
    FString FileName;
};

USTRUCT()
struct UROBOSIM_API FSDFFarClip : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFFarClip();
};

USTRUCT()
struct UROBOSIM_API FSDFNearClip : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFNearClip();
};

USTRUCT()
struct UROBOSIM_API FSDFFov : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFFov();
};

USTRUCT()
struct UROBOSIM_API FSDFTexture : public FSDFStringElement
{
    GENERATED_BODY()
public:
    FSDFTexture();
};


USTRUCT()
struct UROBOSIM_API FSDFMass : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFMass();
};

USTRUCT()
struct UROBOSIM_API FSDFInertia : public FSDFElement
{
    GENERATED_BODY()
public:
    FSDFInertia();
    FSDFIXX Ixx;
    FSDFIXY Ixy;
    FSDFIXZ Ixz;
    FSDFIYY Iyy;
    FSDFIYZ Iyz;
    FSDFIZZ Izz;
};

USTRUCT()
struct UROBOSIM_API FSDFAngular : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFAngular();
};

USTRUCT()
struct UROBOSIM_API FSDFLinear : public FSDFFloatElement
{
    GENERATED_BODY()
public:
    FSDFLinear();
};


USTRUCT()
struct UROBOSIM_API FSDFGravity : public FSDFBoolElement
{
    GENERATED_BODY()
public:
    FSDFGravity();
};

USTRUCT()
struct UROBOSIM_API FSDFEnableWind : public FSDFBoolElement
{
    GENERATED_BODY()
public:
    FSDFEnableWind();
};

USTRUCT()
struct UROBOSIM_API FSDFSelfColide : public FSDFBoolElement
{
    GENERATED_BODY()
public:
    FSDFSelfColide();
};

USTRUCT()
struct UROBOSIM_API FSDFKinematic : public FSDFBoolElement
{
    GENERATED_BODY()
public:
    FSDFKinematic();
};

USTRUCT()
struct UROBOSIM_API FSDFMustBeBaseLink : public FSDFBoolElement
{
    GENERATED_BODY()
public:
    FSDFMustBeBaseLink();
};

USTRUCT()
struct UROBOSIM_API FSDFVelocityDecay : public FSDFElement
{
    GENERATED_BODY()
public:
    FSDFVelocityDecay();
    FSDFAngular Angular;
    FSDFLinear Linear;
};

USTRUCT()
struct UROBOSIM_API FSDFFrame : public FSDFElement
{
    GENERATED_BODY()
public:
    FSDFFrame();
    FString Name;
    FSDFPose Pose;
};


USTRUCT()
struct UROBOSIM_API FSDFInertial : public FSDFElement
{
    GENERATED_BODY()
public:
    FSDFInertial();
    FSDFMass Mass;
    FSDFInertia Inertia;
    FSDFFrame Frame;
    FSDFPose Pose;
};

USTRUCT()
struct UROBOSIM_API FSDFCollision : public FSDFStringElement
{
    GENERATED_BODY()
public:
    FSDFCollision();
};

USTRUCT()
struct UROBOSIM_API FSDFVisual : public FSDFElement
{
    GENERATED_BODY()
public:
    FSDFVisual();
};

USTRUCT()
struct UROBOSIM_API FSDFSensor : public FSDFElement
{
    GENERATED_BODY()
public:
    FSDFSensor();
};

USTRUCT()
struct UROBOSIM_API FSDFProjector : public FSDFElement
{
    GENERATED_BODY()
public:
    FSDFProjector();

    FString Name;
    FSDFTexture Texture;
    FSDFFov Fov;
    FSDFNearClip NearClip;
    FSDFFarClip FarClip;
    FSDFFrame Frame;
    FSDFPose Pose;
    FSDFPlugin Plugin;
};

USTRUCT()
struct UROBOSIM_API FSDFAudioSink : public FSDFElement
{
    GENERATED_BODY()
public:
    FSDFAudioSink();
};

USTRUCT()
struct UROBOSIM_API FSDFAudioSource : public FSDFElement
{
    GENERATED_BODY()
public:
    FSDFAudioSource();
    FSDFUri Uri;
    FSDFPitch Pitch;
    FSDFGain Gain;
    FSDFContact Contact;
    FSDFLoop Loop;
    FSDFFrame Frame;
    FSDFPose Pose;
};

USTRUCT()
struct UROBOSIM_API FSDFBattery : public FSDFElement
{
    GENERATED_BODY()
public:
    FSDFBattery();
    FString Name;
    FSDFVoltage Voltage;
};

UCLASS()
class UROBOSIM_API URLinkDescription : public UObject
{
    GENERATED_BODY()
public:
};


UCLASS()
class UROBOSIM_API URJointDescription : public UObject
{
    GENERATED_BODY()
public:

};

