// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "RStaticMeshComponent.h"
#include "RLink.generated.h"

/**
 *
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UROBOSIM_API URLink : public USceneComponent
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere)
    TArray<UStaticMeshComponent*> MeshComponents;



};
