// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ROSBridgeHandler.h"
#include "ROSBridgePublisher.h"
#include "RPublisher.h"
#include "RPublisherComponent.generated.h"

class ARRobot;
//TODO add create custom message in namespace
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UROBOSIM_API URPublisherComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    URPublisherComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    virtual void EndPlay(const EEndPlayReason::Type Reason) override;

    virtual void CreateAllPublishers();

    UPROPERTY(EditAnywhere, Category = "ROS Bridge Robot")
        FString RobotName;

    UPROPERTY(EditAnywhere, Category = "ROS Bridge Robot")
        TMap<FString,bool> RosTopics;

    UPROPERTY(EditAnywhere, Category = "ROS Bridge Robot")
        FString WebsocketIPAddr;

    UPROPERTY(EditAnywhere, Category = "ROS Bridge Robot")
        uint32 WebsocketPort;

    // Counter
    uint32 TickCount;

    // Pointer to robot
    ARRobot* Robot;

    // ROS Handler
    TSharedPtr<FROSBridgeHandler> Handler;

    UPROPERTY(EditAnywhere, Category = "Publisher List")
        bool bEnableJointStatePublisher;

    UPROPERTY()
        URPublisherFactory* PublisherFactory;

    UPROPERTY()
        TArray<URPublisher* >PublisherList;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
};
