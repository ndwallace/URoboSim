// Fill out your copyright notice in the Description page of Project Settings.


#include "RSubscriber.h"
#include "RPublisherSubscriberComponent.h"

URSubscriber::URSubscriber()
{
}

URSubscriber::~URSubscriber()
{
}

URSubscriber* URSubscriberFactory::CreateSubscriber(URPublisherSubscriberComponent* Owner, FString Topic)
{
    URSubscriber* Subscriber = nullptr;
    // if(Topic.Equals("JointState"))
    // {
    //     Subscriber = NewObject<URJointStatePublisher>(Owner, "JointStatePublisher");
    // }
    // else if(Topic.Equals("String"))
    // {
    //     Subscriber = NewObject<URStringPublisher>(Owner, "StringPublisher");
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Error, TEXT("Topic not known. No Subscriber Created"));
    // }

    return Subscriber;
}

