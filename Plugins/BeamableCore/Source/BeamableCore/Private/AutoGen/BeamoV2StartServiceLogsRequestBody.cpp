
#include "BeamableCore/Public/AutoGen/BeamoV2StartServiceLogsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2StartServiceLogsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("endTime"), &EndTime, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamBeamoV2OrderDirection>(TEXT("order"), &Order, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("filters"), &Filters, Serializer);
}

void UBeamoV2StartServiceLogsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("serviceName"), &ServiceName, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("endTime"), &EndTime, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamBeamoV2OrderDirection>(TEXT("order"), &Order, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("filters"), &Filters, Serializer);		
}

void UBeamoV2StartServiceLogsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("serviceName", Bag, ServiceName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("startTime", Bag, StartTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("endTime", Bag, EndTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<EBeamBeamoV2OrderDirection>("order", Bag, Order, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("filters", Bag, Filters, OuterOwner);
}



