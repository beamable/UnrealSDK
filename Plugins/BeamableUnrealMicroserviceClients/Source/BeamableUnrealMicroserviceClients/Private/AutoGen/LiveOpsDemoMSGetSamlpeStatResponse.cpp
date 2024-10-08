
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSGetSamlpeStatResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void ULiveOpsDemoMSGetSamlpeStatResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<int32>(ResponseContent, Value, OuterOwner);
}

void ULiveOpsDemoMSGetSamlpeStatResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), Value);
}

void ULiveOpsDemoMSGetSamlpeStatResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), Value);		
}

void ULiveOpsDemoMSGetSamlpeStatResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Value = Bag->GetIntegerField(TEXT("Value"));
}



