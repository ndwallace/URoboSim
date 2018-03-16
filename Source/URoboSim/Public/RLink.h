// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Components/MeshComponent.h"
#include "RStaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "RLink.generated.h"

/**
 *
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UROBOSIM_API URLink : public USceneComponent
{
    GENERATED_BODY()
public:
    URLink()
    {
    }


    UPROPERTY(EditAnywhere)
    TArray<UStaticMeshComponent*> MeshComponents;

    void LoadMesh()
    {
        UE_LOG(LogTemp, Warning, TEXT("Tst"));
        static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("StaticMesh'/Game/pr2/base.base'"));
    MeshComponents.Add(NewObject<UStaticMeshComponent>(this));
    MeshComponents[0]->SetStaticMesh(SphereVisualAsset.Object);
    MeshComponents[0]->SetupAttachment(this);
    MeshComponents.Add(NewObject<UStaticMeshComponent>(this));
    MeshComponents[1]->SetStaticMesh(SphereVisualAsset.Object);
    MeshComponents[1]->SetRelativeLocation(FVector(0.0f, 40.0f, 0.0f));
    MeshComponents[1]->SetupAttachment(this);
    MeshComponents.Add(NewObject<UStaticMeshComponent>(this));
    MeshComponents[2]->SetStaticMesh(SphereVisualAsset.Object);
    MeshComponents[2]->SetRelativeLocation(FVector(0.0f, 80.0f, 0.0f));
    MeshComponents[2]->SetupAttachment(this);
    MeshComponents.Add(NewObject<UStaticMeshComponent>(this));
    MeshComponents[3]->SetStaticMesh(SphereVisualAsset.Object);
    MeshComponents[3]->SetRelativeLocation(FVector(0.0f,120.0f, 0.0f));
    MeshComponents[3]->SetupAttachment(this);


    for (auto& MeshComp : MeshComponents)
    {
        MeshComp->SetSimulatePhysics(true);
        MeshComp->SetEnableGravity(true);
    }
    };

};
