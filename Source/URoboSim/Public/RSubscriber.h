// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
