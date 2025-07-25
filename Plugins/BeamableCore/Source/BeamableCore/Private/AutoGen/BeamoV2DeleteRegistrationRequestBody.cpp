
#include "BeamableCore/Public/AutoGen/BeamoV2DeleteRegistrationRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2DeleteRegistrationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
}

void UBeamoV2DeleteRegistrationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);		
}

void UBeamoV2DeleteRegistrationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("routingKey", Bag, RoutingKey, OuterOwner);
}



