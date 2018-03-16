// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RLink.h"
#include "TestLink.generated.h"

UCLASS()
class UROBOSIM_API ATestLink : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestLink();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    URLink * Link;

    URLink * Link2;

};
