
#include "BeamableCore/Public/AutoGen/BeamoV2GetServiceSecretResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UBeamoV2GetServiceSecretResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UBeamoV2GetServiceSecretResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("secret"), &Secret, Serializer);
}

void UBeamoV2GetServiceSecretResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("secret"), &Secret, Serializer);		
}

void UBeamoV2GetServiceSecretResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("secret", Bag, Secret, OuterOwner);
}



