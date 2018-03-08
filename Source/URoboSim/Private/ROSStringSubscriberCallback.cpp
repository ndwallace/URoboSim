// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "ROSStringSubscriberCallback.h"

FROSStringSubscriberCallback::FROSStringSubscriberCallback(
	ARRobot* InOwner, const FString& InTopic, const FString& InType) :
	FROSBridgeSubscriber(InTopic, InType)
{
	Owner = InOwner;
}

FROSStringSubscriberCallback::~FROSStringSubscriberCallback()
{
}

TSharedPtr<FROSBridgeMsg> FROSStringSubscriberCallback::ParseMessage
(TSharedPtr<FJsonObject> JsonObject) const
{
	TSharedPtr<std_msgs::String> StringMessage =
		MakeShareable<std_msgs::String>(new std_msgs::String());

	StringMessage->FromJson(JsonObject);

	return StaticCastSharedPtr<FROSBridgeMsg>(StringMessage);
}

void FROSStringSubscriberCallback::Callback(TSharedPtr<FROSBridgeMsg> Msg)
{
	// Downcast to subclass using StaticCastSharedPtr function
	TSharedPtr<std_msgs::String> StringMessage = StaticCastSharedPtr<std_msgs::String>(Msg);

	// Do something with the message
	UE_LOG(LogTemp, Log, TEXT("[%s] Message received by %s! Content: %s"),
		*FString(__FUNCTION__), *Owner->GetName(), *StringMessage->GetData());
}
