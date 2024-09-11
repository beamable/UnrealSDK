
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrations.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMicroserviceRegistrations::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	Serializer->WriteValue(TEXT("cid"), Cid);
	Serializer->WriteValue(TEXT("pid"), Pid);
	Serializer->WriteValue(TEXT("instanceCount"), InstanceCount);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startedByGamerTag"), &StartedByGamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("beamoName"), &BeamoName, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<USupportedFederation*>, USupportedFederation*>(TEXT("federation"), &Federation, Serializer);
}

void UMicroserviceRegistrations::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	Serializer->WriteValue(TEXT("cid"), Cid);
	Serializer->WriteValue(TEXT("pid"), Pid);
	Serializer->WriteValue(TEXT("instanceCount"), InstanceCount);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("trafficFilterEnabled"), &bTrafficFilterEnabled, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startedByGamerTag"), &StartedByGamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("routingKey"), &RoutingKey, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("beamoName"), &BeamoName, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<USupportedFederation*>, USupportedFederation*>(TEXT("federation"), &Federation, Serializer);		
}

void UMicroserviceRegistrations::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ServiceName = Bag->GetStringField(TEXT("serviceName"));
	Cid = Bag->GetStringField(TEXT("cid"));
	Pid = Bag->GetStringField(TEXT("pid"));
	InstanceCount = Bag->GetIntegerField(TEXT("instanceCount"));
	UBeamJsonUtils::DeserializeOptional<bool>("trafficFilterEnabled", Bag, bTrafficFilterEnabled, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("startedByGamerTag", Bag, StartedByGamerTag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("routingKey", Bag, RoutingKey, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("beamoName", Bag, BeamoName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<USupportedFederation*>, USupportedFederation*>("federation", Bag, Federation, OuterOwner);
}



