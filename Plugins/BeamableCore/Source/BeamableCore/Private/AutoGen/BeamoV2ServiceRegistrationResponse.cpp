
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2ServiceRegistrationResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2ServiceRegistrationResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceRegistration*>, UBeamoV2ServiceRegistration*>(TEXT("registrations"), &Registrations, Serializer);
}

void UBeamoV2ServiceRegistrationResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2ServiceRegistration*>, UBeamoV2ServiceRegistration*>(TEXT("registrations"), &Registrations, Serializer);		
}

void UBeamoV2ServiceRegistrationResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2ServiceRegistration*>, UBeamoV2ServiceRegistration*>("registrations", Bag, Registrations, OuterOwner);
}



