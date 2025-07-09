
#include "BeamableCore/Public/AutoGen/FederationRegistrationResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UFederationRegistrationResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UFederationRegistrationResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UFederationRegistration*>, UFederationRegistration*>(TEXT("registrations"), &Registrations, Serializer);
}

void UFederationRegistrationResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UFederationRegistration*>, UFederationRegistration*>(TEXT("registrations"), &Registrations, Serializer);		
}

void UFederationRegistrationResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UFederationRegistration*>, UFederationRegistration*>("registrations", Bag, Registrations, OuterOwner);
}



