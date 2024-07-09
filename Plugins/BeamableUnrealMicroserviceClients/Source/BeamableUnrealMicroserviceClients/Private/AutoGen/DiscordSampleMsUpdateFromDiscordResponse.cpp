
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordSampleMsUpdateFromDiscordResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UDiscordSampleMsUpdateFromDiscordResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<bool>(ResponseContent, bValue, OuterOwner);
}

void UDiscordSampleMsUpdateFromDiscordResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);
}

void UDiscordSampleMsUpdateFromDiscordResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), bValue);		
}

void UDiscordSampleMsUpdateFromDiscordResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bValue = Bag->GetBoolField(TEXT("Value"));
}



