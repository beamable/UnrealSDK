
#include "BeamableCore/Public/AutoGen/BeamoV2FederationRegistrationResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2FederationRegistrationResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2FederationRegistrationResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2FederationRegistration*>, UBeamoV2FederationRegistration*>(TEXT("registrations"), &Registrations, Serializer);
}

void UBeamoV2FederationRegistrationResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2FederationRegistration*>, UBeamoV2FederationRegistration*>(TEXT("registrations"), &Registrations, Serializer);		
}

void UBeamoV2FederationRegistrationResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2FederationRegistration*>, UBeamoV2FederationRegistration*>("registrations", Bag, Registrations, OuterOwner);
}



