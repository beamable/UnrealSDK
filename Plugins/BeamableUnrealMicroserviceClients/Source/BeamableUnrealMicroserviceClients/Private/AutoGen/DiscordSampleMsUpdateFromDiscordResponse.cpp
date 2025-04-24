
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordSampleMsUpdateFromDiscordResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UDiscordSampleMsUpdateFromDiscordResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<bool>(ResponseContent, bValue, OuterOwner);
}

void UDiscordSampleMsUpdateFromDiscordResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("Value"), bValue, Serializer);
}

void UDiscordSampleMsUpdateFromDiscordResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("Value"), bValue, Serializer);		
}

void UDiscordSampleMsUpdateFromDiscordResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("Value")), bValue);
}



