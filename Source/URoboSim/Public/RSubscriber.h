// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ROSBridgeHandler.h"
#include "RSubscriber.generated.h"
/**
 *
 */
class URPublisherSubscriberComponent;

UCLASS()
class UROBOSIM_API URSubscriber: public UObject
{
    GENERATED_BODY()
public:
    URSubscriber();
    ~URSubscriber();
    virtual bool Init(FString RosTopic);

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

    URPublisherSubscriberComponent* PublisherSubscriberComponent;
    FString Topic;
};

UCLASS()
class UROBOSIM_API URStringSubscriber: public URSubscriber
{
    GENERATED_BODY()
public:
    URStringSubscriber();
    ~URStringSubscriber();

    virtual bool Init(FString RosTopic);

    TSharedPtr<FROSBridgeSubscriber> Subscriber;
};

UCLASS()
class UROBOSIM_API URSubscriberFactory : public UObject
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    URSubscriberFactory(){};
    URSubscriber* CreateSubscriber(URPublisherSubscriberComponent* Owner, FString Topic);
};
