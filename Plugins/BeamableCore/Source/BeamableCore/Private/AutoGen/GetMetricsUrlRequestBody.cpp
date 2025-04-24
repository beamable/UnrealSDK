
#include "BeamableCore/Public/AutoGen/GetMetricsUrlRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetMetricsUrlRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("metricName"), MetricName, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("endTime"), &EndTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("period"), &Period, Serializer);
}

void UGetMetricsUrlRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("metricName"), MetricName, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("endTime"), &EndTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("period"), &Period, Serializer);		
}

void UGetMetricsUrlRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("serviceName")), ServiceName);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("metricName")), MetricName);
	UBeamJsonUtils::DeserializeOptional<int64>("startTime", Bag, StartTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("endTime", Bag, EndTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("period", Bag, Period, OuterOwner);
}



