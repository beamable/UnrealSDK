
#include "BeamableCore/Public/AutoGen/BeamoV2FederationRegistration.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2FederationRegistration::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("ttl"), &Ttl, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2SupportedFederation*>, UBeamoV2SupportedFederation*>(TEXT("federation"), &Federation, Serializer);
}

void UBeamoV2FederationRegistration::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("ttl"), &Ttl, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2SupportedFederation*>, UBeamoV2SupportedFederation*>(TEXT("federation"), &Federation, Serializer);		
}

void UBeamoV2FederationRegistration::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("trafficFilterEnabled", Bag, bTrafficFilterEnabled, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("serviceName", Bag, ServiceName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("routingKey", Bag, RoutingKey, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("ttl", Bag, Ttl, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2SupportedFederation*>, UBeamoV2SupportedFederation*>("federation", Bag, Federation, OuterOwner);
}



