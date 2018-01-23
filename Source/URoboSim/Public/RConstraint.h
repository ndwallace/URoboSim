// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "IURoboSim.h"
#include "UnrealEd.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "Structs.h"
#include "RArticulation.h"
#include "RConstraint.generated.h"

UCLASS()
class UROBOSIM_API URConstraint : public UPhysicsConstraintComponent
{
  GENERATED_BODY()
	public:
	URConstraint(){};
  virtual void InitDrive(){};
  virtual void Init(URStaticMeshComponent* ParentComp, FRJoint* Joint, FRLink* Link){};
  bool bEnableMotor = false;
  // UPhysicsConstraintComponent* Constraint;
  // FConstraintInstance ConstraintInstance;

};

UCLASS()
class UROBOSIM_API URFixedConstraint : public URConstraint
{
  GENERATED_BODY()
	public:
	URFixedConstraint(){};
  void Init(URStaticMeshComponent* ParentComp, FRJoint* Joint, FRLink* Link);
  void InitDrive(){};
};

UCLASS()
class UROBOSIM_API URFloatingConstraint : public URFixedConstraint
{
  GENERATED_BODY()
	public:
	URFloatingConstraint(){};
  void Init(URStaticMeshComponent* ParentComp, FRJoint* Joint, FRLink* Link);
  void InitDrive(){};
};

UCLASS()
class UROBOSIM_API URPrismaticConstraint : public URFixedConstraint
{
  GENERATED_BODY()
	public:
	URPrismaticConstraint(){};
  void Init(URStaticMeshComponent* ParentComp, FRJoint* Joint, FRLink* Link);
  void InitDrive();
};

UCLASS()
class UROBOSIM_API URRevoluteConstraint : public URFixedConstraint
{
  GENERATED_BODY()
	public:
	URRevoluteConstraint(){};
  void Init(URStaticMeshComponent* ParentComp, FRJoint* Joint, FRLink* Link);
  void InitDrive();
};

UCLASS()
class UROBOSIM_API URPlanarConstraint : public URFixedConstraint
{
  GENERATED_BODY()
	public:
	URPlanarConstraint(){};
  void Init(URStaticMeshComponent* ParentComp, FRJoint* Joint, FRLink* Link);
  void InitDrive(){};
};

UCLASS()
class UROBOSIM_API URContinuousConstraint : public URFixedConstraint
{
  GENERATED_BODY()
	public:
	URContinuousConstraint(){};
  void Init(URStaticMeshComponent* ParentComp, FRJoint* Joint, FRLink* Link);
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
