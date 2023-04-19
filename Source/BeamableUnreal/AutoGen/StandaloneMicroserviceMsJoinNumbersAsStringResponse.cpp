
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsJoinNumbersAsStringResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UStandaloneMicroserviceMsJoinNumbersAsStringResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<FString>(ResponseContent, Value, OuterOwner);
}

void UStandaloneMicroserviceMsJoinNumbersAsStringResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), Value);
}

void UStandaloneMicroserviceMsJoinNumbersAsStringResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), Value);		
}

void UStandaloneMicroserviceMsJoinNumbersAsStringResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Value = Bag->GetStringField(TEXT("Value"));
}



