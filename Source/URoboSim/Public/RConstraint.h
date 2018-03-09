// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "IURoboSim.h"
#include "UnrealEd.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "Structs.h"
#include "RStaticMeshComponent.h"
#include "RConstraint.generated.h"

class ARRobot;
class URMeshHandler;

UCLASS()
class UROBOSIM_API URConstraint : public UPhysicsConstraintComponent
{
    GENERATED_BODY()
public:
    URConstraint();
    UPROPERTY()
    URMeshHandler* MeshHandler;

    virtual void BeginPlay() override;

    // Configures the Unreal Engine native joint drive
    virtual void InitDrive(){};
    // Initializes and configures the contraint/ joint
    virtual void Init(URMeshHandler* MeshH);
    // Connects joint and links
    virtual void SetupConstraint(){};
    bool bEnableMotor = false;

    virtual float GetJointPosition();
    virtual float GetJointVelocity();

    virtual URStaticMeshComponent* Child();
    virtual URStaticMeshComponent* Parent();

    UPROPERTY()
    FString Type;

    UPROPERTY()
    FString ChildName;

    UPROPERTY()
    FString ParentName;

    UPROPERTY()
    ARRobot* Owner;
};

UCLASS()
class UROBOSIM_API URFixedConstraint : public URConstraint
{
    GENERATED_BODY()
public:
    URFixedConstraint();

    // Initializes and configures the contraint/ joint
    void Init(URMeshHandler* MeshH);
    // Configures the Unreal Engine native joint drive
    void InitDrive(){};
    // Connects joint and links
    void SetupConstraint();
    float CreateContraintLimit();

    virtual float GetJointPosition();
    virtual float GetJointVelocity();
};

UCLASS()
class UROBOSIM_API URFloatingConstraint : public URFixedConstraint
{
    GENERATED_BODY()
public:
    URFloatingConstraint();
    // Initializes and configures the contraint/ joint
    void Init(URMeshHandler* MeshH);
    // Configures the Unreal Engine native joint drive
    void InitDrive(){};
};

UCLASS()
class UROBOSIM_API URPrismaticConstraint : public URFixedConstraint
{
    GENERATED_BODY()
public:
    URPrismaticConstraint();
    // Initializes and configures the contraint/ joint
    void Init(URMeshHandler* MeshH);
    // Configures the Unreal Engine native joint drive
    void InitDrive();

    virtual float GetJointPosition();
    virtual float GetJointVelocity();
};

UCLASS()
class UROBOSIM_API URRevoluteConstraint : public URFixedConstraint
{
    GENERATED_BODY()
public:
    URRevoluteConstraint();
    // Initializes and configures the contraint/ joint
    void Init(URMeshHandler* MeshH);
    // Configures the Unreal Engine native joint drive
    void InitDrive();

    virtual float GetJointPosition();
    virtual float GetJointVelocity();
};

UCLASS()
class UROBOSIM_API URPlanarConstraint : public URFixedConstraint
{
    GENERATED_BODY()
public:
    URPlanarConstraint();
    // Initializes and configures the contraint/ joint
    void Init(URMeshHandler* MeshH);
    // Configures the Unreal Engine native joint drive
    void InitDrive(){};
};

UCLASS()
class UROBOSIM_API URContinuousConstraint : public URRevoluteConstraint
{
    GENERATED_BODY()
public:
    URContinuousConstraint();
    // Initializes and configures the contraint/ joint
    void Init(URMeshHandler* MeshH);
    // Configures the Unreal Engine native joint drive
    void InitDrive();
};

// UCLASS()
// class  UROBOSIM_API URConstraintFactory : public UFactory
// {
//   GENERATED_BODY()
// private:
// 	URConstraintFactory(const FObjectInitializer& ObjectInitializer);

// 	public:
//     UPROPERTY()
// 	TSubclassOf<class URConstraint>  NewConstraintClass;
// 	static URConstraint* MakeConstraint(URStaticMeshComponent* ParentComp, FRJoint* Joint, FRLink* Link);
// 	virtual ~URConstraintFactory();
// };

// UCLASS()
// class  UROBOSIM_API URConstraintFactory : public UObject
// {
//   GENERATED_BODY()
// 	public:
// 	URConstraintFactory(){};
// 	static URConstraint* MakeConstraint(URStaticMeshComponent* ParentComp, FRJoint* Joint, FRLink* Link);

// };
