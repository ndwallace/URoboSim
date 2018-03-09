// Fill out your copyright notice in the Description page of Project Settings.


#include "RPublisherSubscriberComponent.h"
#include "RRobot.h"

// Sets default values for this component's properties
URPublisherSubscriberComponent::URPublisherSubscriberComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    PrimaryComponentTick.bCanEverTick = true;

    WebsocketIPAddr = TEXT("127.0.0.1");
    WebsocketPort = 9090;
    RobotName = TEXT("pr2_base");
    TickCount = 0;
    RosPublisherTopics.Add("JointState",true);
    RosPublisherTopics.Add("unreal_to_ros_string", false);
    RosSubscriberTopics.Add("ros_to_unreal_string", false);
    PublisherFactory = CreateDefaultSubobject<URPublisherFactory>(FName(TEXT("PublisherFactory")));
    SubscriberFactory = CreateDefaultSubobject<URSubscriberFactory>(FName(TEXT("SubscriberFactory")));
}


// Called when the game starts
void URPublisherSubscriberComponent::BeginPlay()
{
    Super::BeginPlay();
    Owner = Cast<ARRobot>(GetOwner());
    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(WebsocketIPAddr, WebsocketPort));
    Handler->Connect();
    CreateAllPublishers();
    CreateAllSubscriber();
}


void URPublisherSubscriberComponent::CreateAllSubscriber()
{
    for(auto& Topic : RosSubscriberTopics)
    {
        if(Topic.Value)
        {
            URSubscriber* TempSubscriber = SubscriberFactory->CreateSubscriber(this, Topic.Key);
            if(TempSubscriber)
            {
                TempSubscriber->Init( Topic.Key);
                SubscriberList.Add(TempSubscriber);
            }
        }
    }
}

void URPublisherSubscriberComponent::CreateAllPublishers()
{
    for(auto& Topic : RosPublisherTopics)
    {
        if(Topic.Value)
        {
            URPublisher* TempPublisher = PublisherFactory->CreatePublisher(this, Topic.Key);
            if(TempPublisher)
            {
                TempPublisher->Init( Topic.Key);
                PublisherList.Add(TempPublisher);
            }
        }
    }
}

// Called every frame
void URPublisherSubscriberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    ++TickCount;
    for(auto& Publisher : PublisherList)
    {
        Publisher->Publish();
    }
}

void URPublisherSubscriberComponent::EndPlay(const EEndPlayReason::Type Reason)
{
    //Disconnect the handler before parent ends

    Handler->Disconnect();
    Super::EndPlay(Reason);
}
