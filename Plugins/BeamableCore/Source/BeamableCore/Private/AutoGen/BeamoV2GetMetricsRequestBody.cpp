
#include "BeamableCore/Public/AutoGen/BeamoV2GetMetricsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2GetMetricsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("metricName"), &MetricName, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("endTime"), &EndTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("period"), &Period, Serializer);
}

void UBeamoV2GetMetricsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("metricName"), &MetricName, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("endTime"), &EndTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("period"), &Period, Serializer);		
}

void UBeamoV2GetMetricsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("metricName", Bag, MetricName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("startTime", Bag, StartTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("endTime", Bag, EndTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("period", Bag, Period, OuterOwner);
}



