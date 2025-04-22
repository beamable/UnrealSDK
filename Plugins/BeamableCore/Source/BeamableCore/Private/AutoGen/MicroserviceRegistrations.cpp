
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrations.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMicroserviceRegistrations::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cid"), Cid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("pid"), Pid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("instanceCount"), InstanceCount, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startedById"), &StartedById, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("beamoName"), &BeamoName, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<USupportedFederation*>, USupportedFederation*>(TEXT("federation"), &Federation, Serializer);
}

void UMicroserviceRegistrations::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cid"), Cid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("pid"), Pid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("instanceCount"), InstanceCount, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startedById"), &StartedById, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("beamoName"), &BeamoName, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<USupportedFederation*>, USupportedFederation*>(TEXT("federation"), &Federation, Serializer);		
}

void UMicroserviceRegistrations::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("serviceName")), ServiceName);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("cid")), Cid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("pid")), Pid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("instanceCount")), InstanceCount);
	UBeamJsonUtils::DeserializeOptional<bool>("trafficFilterEnabled", Bag, bTrafficFilterEnabled, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("routingKey", Bag, RoutingKey, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("startedById", Bag, StartedById, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("beamoName", Bag, BeamoName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<USupportedFederation*>, USupportedFederation*>("federation", Bag, Federation, OuterOwner);
}



