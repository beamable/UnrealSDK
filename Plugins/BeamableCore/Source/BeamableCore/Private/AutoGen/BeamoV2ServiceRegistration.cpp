
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistration.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ServiceRegistration::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("instanceCount"), &InstanceCount, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("beamoName"), &BeamoName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startedById"), &StartedById, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2SupportedFederation*>, UBeamoV2SupportedFederation*>(TEXT("federation"), &Federation, Serializer);
}

void UBeamoV2ServiceRegistration::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("instanceCount"), &InstanceCount, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("beamoName"), &BeamoName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startedById"), &StartedById, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UBeamoV2SupportedFederation*>, UBeamoV2SupportedFederation*>(TEXT("federation"), &Federation, Serializer);		
}

void UBeamoV2ServiceRegistration::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("trafficFilterEnabled", Bag, bTrafficFilterEnabled, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("instanceCount", Bag, InstanceCount, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("serviceName", Bag, ServiceName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("cid", Bag, Cid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("pid", Bag, Pid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("beamoName", Bag, BeamoName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("routingKey", Bag, RoutingKey, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("startedById", Bag, StartedById, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UBeamoV2SupportedFederation*>, UBeamoV2SupportedFederation*>("federation", Bag, Federation, OuterOwner);
}



