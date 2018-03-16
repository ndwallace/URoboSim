// Fill out your copyright notice in the Description page of Project Settings.


#include "RRobotAsset.h"


void URobotAsset::CreateComponentDescriptions(TArray<URElement*> ComponentList)
{
    for(auto& Component : ComponentList)
    {
        if(Component->Elements["name"].Equals("link"))
        {
            CreateLinkDescription(Component);
        }
        else if(Component->Elements["name"].Equals("joint"))
        {
            CreateJointDescription(Component);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Component Type not supported"));
        }
    }
}

void URobotAsset::CreateLinkDescription(URElement* Component)
{

}

void URobotAsset::CreateJointDescription(URElement* Component)
{

}





