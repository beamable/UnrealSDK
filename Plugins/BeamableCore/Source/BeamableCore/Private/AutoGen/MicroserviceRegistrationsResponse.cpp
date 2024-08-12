
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UMicroserviceRegistrationsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMicroserviceRegistrationsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UMicroserviceRegistrations*>(TEXT("registrations"), Registrations, Serializer);
}

void UMicroserviceRegistrationsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UMicroserviceRegistrations*>(TEXT("registrations"), Registrations, Serializer);		
}

void UMicroserviceRegistrationsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UMicroserviceRegistrations*>(Bag->GetArrayField(TEXT("registrations")), Registrations, OuterOwner);
}



