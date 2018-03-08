// Fill out your copyright notice in the Description page of Project Settings.


#include "RPublisherComponent.h"
#include "RRobot.h"

// Sets default values for this component's properties
URPublisherComponent::URPublisherComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    PrimaryComponentTick.bCanEverTick = true;
    bEnableJointStatePublisher = true;

    WebsocketIPAddr = TEXT("127.0.0.1");
    WebsocketPort = 9001;
    RobotName = TEXT("pr2_base");
    TickCount = 0;
    RosTopics.Add("JointState",false);
    RosTopics.Add("String", true);
    PublisherFactory = CreateDefaultSubobject<URPublisherFactory>(FName(TEXT("PublisherFactory")));
}


// Called when the game starts
void URPublisherComponent::BeginPlay()
{
    Super::BeginPlay();
    Robot = Cast<ARRobot>(GetOwner());
    Handler = MakeShareable<FROSBridgeHandler>(new FROSBridgeHandler(WebsocketIPAddr, WebsocketPort));
    Handler->Connect();
    CreateAllPublishers();
}

void URPublisherComponent::CreateAllPublishers()
{
    for(auto& Topic : RosTopics)
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
void URPublisherComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    ++TickCount;
}

void URPublisherComponent::EndPlay(const EEndPlayReason::Type Reason)
{
    //Disconnect the handler before parent ends

    Handler->Disconnect();
    Super::EndPlay(Reason);
}
