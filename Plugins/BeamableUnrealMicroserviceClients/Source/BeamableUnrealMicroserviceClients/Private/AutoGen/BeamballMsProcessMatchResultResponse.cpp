
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballMsProcessMatchResultResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamballMsProcessMatchResultResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<TMap<FString, FString>>(ResponseContent, Value, OuterOwner);
}

void UBeamballMsProcessMatchResultResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<>(TEXT("Value"), Value, Serializer);
}

void UBeamballMsProcessMatchResultResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<>(TEXT("Value"), Value, Serializer);		
}

void UBeamballMsProcessMatchResultResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeMap<>(TEXT("Value"), Bag, Value, OuterOwner);
}



