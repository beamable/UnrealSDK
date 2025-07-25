
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationQuery.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ServiceRegistrationQuery::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("localOnly"), &bLocalOnly, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<UBeamoV2SupportedFederation*>(TEXT("federation"), &Federation, Serializer);
}

void UBeamoV2ServiceRegistrationQuery::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("localOnly"), &bLocalOnly, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<UBeamoV2SupportedFederation*>(TEXT("federation"), &Federation, Serializer);		
}

void UBeamoV2ServiceRegistrationQuery::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("localOnly", Bag, bLocalOnly, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("serviceName", Bag, ServiceName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("routingKey", Bag, RoutingKey, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UBeamoV2SupportedFederation*>("federation", Bag, Federation, OuterOwner);
}



