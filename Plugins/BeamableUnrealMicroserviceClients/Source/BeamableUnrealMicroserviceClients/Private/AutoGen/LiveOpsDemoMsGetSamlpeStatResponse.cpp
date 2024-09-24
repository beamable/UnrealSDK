
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsGetSamlpeStatResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void ULiveOpsDemoMsGetSamlpeStatResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<int32>(ResponseContent, Value, OuterOwner);
}

void ULiveOpsDemoMsGetSamlpeStatResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), Value);
}

void ULiveOpsDemoMsGetSamlpeStatResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), Value);		
}

void ULiveOpsDemoMsGetSamlpeStatResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Value = Bag->GetIntegerField(TEXT("Value"));
}



