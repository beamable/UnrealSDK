
#include "BeamableCore/Public/AutoGen/SupportedFederationsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void USupportedFederationsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USupportedFederationsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<USupportedFederationRegistration*>(TEXT("registrations"), Registrations, Serializer);
}

void USupportedFederationsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<USupportedFederationRegistration*>(TEXT("registrations"), Registrations, Serializer);		
}

void USupportedFederationsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<USupportedFederationRegistration*>(Bag->GetArrayField(TEXT("registrations")), Registrations, OuterOwner);
}



