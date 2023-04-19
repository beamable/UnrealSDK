
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsAddResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UStandaloneMicroserviceMsAddResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<int32>(ResponseContent, Value, OuterOwner);
}

void UStandaloneMicroserviceMsAddResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), Value);
}

void UStandaloneMicroserviceMsAddResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), Value);		
}

void UStandaloneMicroserviceMsAddResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Value = Bag->GetIntegerField(TEXT("Value"));
}



