// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ROSBridgeHandler.h"
#include "ROSBridgePublisher.h"
#include "RPublisher.generated.h"

class  ARRobot;
class URPublisherComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UROBOSIM_API URPublisher : public UObject
{
    GENERATED_BODY()
public:
    URPublisherComponent* PublisherComponent;
    FString Topic;


    // Sets default values for this component's properties
    URPublisher();
    virtual bool Init(FString Topic);
    virtual void Publish(){};

    template<typename T>
    bool CheckPointer(T* Pointer)
    {
        if(Pointer)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UROBOSIM_API URJointStatePublisher : public URPublisher
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    URJointStatePublisher();

    virtual bool Init(FString Topic);
    virtual void Publish();

    // ROS Publisher
    TSharedPtr<FROSBridgePublisher> Publisher;
};

UCLASS()
class UROBOSIM_API URStringPublisher : public URPublisher
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    URStringPublisher();
    virtual bool Init(FString Topic);
    virtual void Publish();

    TSharedPtr<FROSBridgePublisher> Publisher;
};

UCLASS()
class UROBOSIM_API URPublisherFactory : public UObject
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    URPublisherFactory(){};
    URPublisher* CreatePublisher(URPublisherComponent* Owner, FString Topic);
};
