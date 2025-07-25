
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ServiceRegistrationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2SupportedFederation*>, UBeamoV2SupportedFederation*>(TEXT("federation"), &Federation, Serializer);
}

void UBeamoV2ServiceRegistrationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2SupportedFederation*>, UBeamoV2SupportedFederation*>(TEXT("federation"), &Federation, Serializer);		
}

void UBeamoV2ServiceRegistrationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("routingKey", Bag, RoutingKey, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("trafficFilterEnabled", Bag, bTrafficFilterEnabled, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2SupportedFederation*>, UBeamoV2SupportedFederation*>("federation", Bag, Federation, OuterOwner);
}



