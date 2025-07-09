
#include "BeamableCore/Public/AutoGen/ServiceRegistrationResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UServiceRegistrationResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UServiceRegistrationResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UServiceRegistration*>, UServiceRegistration*>(TEXT("registrations"), &Registrations, Serializer);
}

void UServiceRegistrationResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UServiceRegistration*>, UServiceRegistration*>(TEXT("registrations"), &Registrations, Serializer);		
}

void UServiceRegistrationResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceRegistration*>, UServiceRegistration*>("registrations", Bag, Registrations, OuterOwner);
}



