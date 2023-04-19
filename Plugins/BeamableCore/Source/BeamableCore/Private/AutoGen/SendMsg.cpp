
#include "BeamableCore/Public/AutoGen/SendMsg.h"
#include "Serialization/BeamJsonUtils.h"




void USendMsg::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<int64>(TEXT("to"), To, Serializer);
	UBeamJsonUtils::SerializeOptional<USendNotification*>(TEXT("notification"), &Notification, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("data"), &Data, Serializer);
}

void USendMsg::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<int64>(TEXT("to"), To, Serializer);
	UBeamJsonUtils::SerializeOptional<USendNotification*>(TEXT("notification"), &Notification, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("data"), &Data, Serializer);		
}

void USendMsg::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<int64>(Bag->GetArrayField(TEXT("to")), To, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<USendNotification*>("notification", Bag, Notification, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("data", Bag, Data, OuterOwner);
}



