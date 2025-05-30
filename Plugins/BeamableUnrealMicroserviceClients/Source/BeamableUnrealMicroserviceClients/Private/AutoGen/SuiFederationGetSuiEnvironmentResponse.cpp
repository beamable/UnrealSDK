
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SuiFederationGetSuiEnvironmentResponse.h"
#include "Serialization/BeamJsonUtils.h"



void USuiFederationGetSuiEnvironmentResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	UBeamJsonUtils::DeserializeRawPrimitive<FString>(ResponseContent, Value, OuterOwner);
}

void USuiFederationGetSuiEnvironmentResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), Value);
}

void USuiFederationGetSuiEnvironmentResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("Value"), Value);		
}

void USuiFederationGetSuiEnvironmentResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Value = Bag->GetStringField(TEXT("Value"));
}



