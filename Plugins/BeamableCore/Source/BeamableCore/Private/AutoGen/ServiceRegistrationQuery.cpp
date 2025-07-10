
#include "BeamableCore/Public/AutoGen/ServiceRegistrationQuery.h"
#include "Serialization/BeamJsonUtils.h"




void UServiceRegistrationQuery::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("localOnly"), &bLocalOnly, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<USupportedFederation*>(TEXT("federation"), &Federation, Serializer);
}

void UServiceRegistrationQuery::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("localOnly"), &bLocalOnly, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<USupportedFederation*>(TEXT("federation"), &Federation, Serializer);		
}

void UServiceRegistrationQuery::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("localOnly", Bag, bLocalOnly, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("serviceName", Bag, ServiceName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("routingKey", Bag, RoutingKey, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<USupportedFederation*>("federation", Bag, Federation, OuterOwner);
}



