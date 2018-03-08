// Fill out your copyright notice in the Description page of Project Settings.


#include "RSubscriber.h"
#include "RPublisherSubscriberComponent.h"
#include "ROSStringSubscriberCallback.h"
#include "std_msgs/String.h"

URSubscriber::URSubscriber()
{
}

URSubscriber::~URSubscriber()
{
}


bool URSubscriber::Init(FString RosTopic)
{
    Topic = RosTopic;
    PublisherSubscriberComponent = Cast<URPublisherSubscriberComponent>(GetOuter());
    return CheckPointer(PublisherSubscriberComponent);
}


URStringSubscriber::URStringSubscriber()
{
}

URStringSubscriber::~URStringSubscriber()
{
}

bool URStringSubscriber::Init(FString RosTopic)
{
    if(Super::Init(RosTopic))
    {
        Subscriber = MakeShareable<FROSStringSubscriberCallback>(
                new FROSStringSubscriberCallback(PublisherSubscriberComponent->Owner, Topic, TEXT("std_msgs/String"))
                );
        PublisherSubscriberComponent->Handler->AddSubscriber(Subscriber);
    }
    return true;
}

URSubscriber* URSubscriberFactory::CreateSubscriber(URPublisherSubscriberComponent* Owner, FString Topic)
{
    URSubscriber* Subscriber = nullptr;
    if(Topic.Equals("ros_to_unreal_string"))
    {
        Subscriber = NewObject<URStringSubscriber>(Owner, "StringSubscriber");
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Topic not known. No Subscriber Created"));
    }

    return Subscriber;
}

