// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLink.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"


// Sets default values
ATestLink::ATestLink()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
	PrimaryActorTick.bCanEverTick = true;
    Link = CreateDefaultSubobject<URLink>(TEXT("Link"));
    Link->SetupAttachment(Root);
    Link->LoadMesh();

    Link2 = CreateDefaultSubobject<URLink>(TEXT("Link2"));
    Link2->SetupAttachment(Root);
    Link2->LoadMesh();
}

// Called when the game starts or when spawned
void ATestLink::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATestLink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

