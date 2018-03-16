// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RFileParser.h"
#include "RSDFElements.h"
#include "RRobotAsset.generated.h"


/**
 * Containts the Link and Joint information of the  robot used to spawn it.
 */
UCLASS()
class UROBOSIM_API URobotAsset : public UDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere)
    TArray<URLinkDescription *> LinkList;

    UPROPERTY(EditAnywhere)
    TArray<URJointDescription*> JointList;

    void CreateComponentDescriptions(TArray<URElement*> ComponentList);
    void CreateLinkDescription(URElement* Component);
    void CreateJointDescription(URElement* Component);
};
