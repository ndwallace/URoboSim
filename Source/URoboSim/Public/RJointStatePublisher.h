// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ROSBridgeHandler.h"
#include "ROSBridgePublisher.h"
#include "RJointStatePublisher.generated.h"

class  ARRobot;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UROBOSIM_API URJointStatePublisher : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    URJointStatePublisher();

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    UPROPERTY(EditAnywhere, Category = "ROS Bridge Robot")
        FString RobotName;

    UPROPERTY(EditAnywhere, Category = "ROS Bridge Robot")
        FString RobotJointStateTopic;

    UPROPERTY(EditAnywhere, Category = "ROS Bridge Robot")
        FString RobotEffortTopic;

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

    // ROS Publisher
    TSharedPtr<FROSBridgePublisher> RobotJointStatePublisher;

    // ROS Subscriber
    TSharedPtr<FRobotForceSubscriberCallback> RobotForceSubscriber;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;



};
