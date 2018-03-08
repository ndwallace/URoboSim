// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "CoreMinimal.h"
#include "RRobot.h"

#include "ROSBridgeHandler.h"
#include "ROSBridgeSubscriber.h"
#include "std_msgs/String.h"

/**
 *
 */
class UROBOSIM_API FROSStringSubscriberCallback : public FROSBridgeSubscriber
{
public:
	FROSStringSubscriberCallback(ARRobot* InOwner, const FString& InTopic, const FString& InType);

	~FROSStringSubscriberCallback() override;

	TSharedPtr<FROSBridgeMsg> ParseMessage(TSharedPtr<FJsonObject> JsonObject) const override;

	void Callback(TSharedPtr<FROSBridgeMsg> Msg) override;

private:
	ARRobot* Owner;
};
