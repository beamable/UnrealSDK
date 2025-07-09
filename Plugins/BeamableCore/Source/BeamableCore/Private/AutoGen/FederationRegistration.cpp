
#include "BeamableCore/Public/AutoGen/FederationRegistration.h"
#include "Serialization/BeamJsonUtils.h"




void UFederationRegistration::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("ttl"), &Ttl, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<USupportedFederation*>, USupportedFederation*>(TEXT("federation"), &Federation, Serializer);
}

void UFederationRegistration::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("ttl"), &Ttl, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<USupportedFederation*>, USupportedFederation*>(TEXT("federation"), &Federation, Serializer);		
}

void UFederationRegistration::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("trafficFilterEnabled", Bag, bTrafficFilterEnabled, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("serviceName", Bag, ServiceName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("routingKey", Bag, RoutingKey, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("ttl", Bag, Ttl, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<USupportedFederation*>, USupportedFederation*>("federation", Bag, Federation, OuterOwner);
}



