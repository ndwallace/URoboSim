// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
    virtual void PostActorCreated() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    UPROPERTY(EditAnywhere)
    // UBrushComponent* Root;
    UStaticMeshComponent* Root;
    UMaterial* Material;
};
