// Fill out your copyright notice in the Description page of Project Settings.


#include "RPublisher.h"
#include "RRobot.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/String.h"
#include "RPublisherSubscriberComponent.h"

URPublisher::URPublisher()
{
}

bool URPublisher::Init(FString RosTopic)
{
    Topic = RosTopic;
    PublisherComponent = Cast<URPublisherSubscriberComponent>(GetOuter());
    return CheckPointer(PublisherComponent);
}

URJointStatePublisher::URJointStatePublisher():Super()
{

}

bool URJointStatePublisher::Init(FString RosTopic)
{
    if(Super::Init(RosTopic))
    {
        Publisher = MakeShareable<FROSBridgePublisher>
            (new FROSBridgePublisher(Topic, TEXT("sensor_msgs/JointState")));

        PublisherComponent->Handler->AddPublisher(Publisher);
    }
    return true;
}

void URJointStatePublisher::Publish()
{
    // Process messages
    PublisherComponent->Handler->Process();

    TArray<FString> ListJointName;
    TArray<double> ListJointPosition, ListJointVelocity;

    for (auto &JointElement : PublisherComponent->Owner->JointComponents)
    {
        FString JointName = JointElement.Value->GetName();
        float JointPosition = JointElement.Value->GetJointAngle();
        float JointVelocity = JointElement.Value->GetJointVelocity();

        ListJointName.Add(JointName);
        ListJointPosition.Add(JointPosition);
        ListJointVelocity.Add(JointVelocity);
    }

    TSharedPtr<sensor_msgs::JointState> JointState =
        MakeShareable(new sensor_msgs::JointState());
    JointState->SetHeader(std_msgs::Header(PublisherComponent->TickCount, FROSTime(), TEXT("0")));
    JointState->SetName(ListJointName);
    JointState->SetPosition(ListJointPosition);
    JointState->SetVelocity(ListJointVelocity);

    PublisherComponent->Handler->PublishMsg(Topic, JointState);

    UE_LOG(LogTemp, Log, TEXT("JointState = %s"), *JointState->ToString());
}

URStringPublisher::URStringPublisher():Super()
{
}

bool URStringPublisher::Init(FString RosTopic)
{
    if(Super::Init(RosTopic))
    {
        Publisher = MakeShareable<FROSBridgePublisher>
            (new FROSBridgePublisher(Topic, TEXT("std_msgs/String")));
        PublisherComponent->Handler->AddPublisher(Publisher);
    }
    return true;
}

void URStringPublisher::Publish()
{
    TSharedPtr<std_msgs::String> UnrealString = MakeShareable(
            new std_msgs::String());
    UnrealString->SetData("Hello World");

    // Send msg to ROS
    PublisherComponent->Handler->PublishMsg(Topic, UnrealString);
    UE_LOG(LogTemp, Log, TEXT("Sending string msg to ROS: %s"), *UnrealString->ToString());

    // Process messages
    PublisherComponent->Handler->Process();
}

URPublisher* URPublisherFactory::CreatePublisher(URPublisherSubscriberComponent* Owner, FString Topic)
{
    URPublisher* Publisher = nullptr;
    if(Topic.Equals("JointState"))
    {
        Publisher = NewObject<URJointStatePublisher>(Owner, "JointStatePublisher");
    }
    else if(Topic.Equals("unreal_to_ros_string"))
    {
        Publisher = NewObject<URStringPublisher>(Owner, "StringPublisher");
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Topic not known. No Publisher Created"));
    }

    return Publisher;
}
