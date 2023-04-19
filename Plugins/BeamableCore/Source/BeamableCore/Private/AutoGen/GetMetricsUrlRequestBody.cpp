
#include "BeamableCore/Public/AutoGen/GetMetricsUrlRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetMetricsUrlRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	Serializer->WriteValue(TEXT("metricName"), MetricName);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("endTime"), &EndTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("period"), &Period, Serializer);
}

void UGetMetricsUrlRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	Serializer->WriteValue(TEXT("metricName"), MetricName);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("endTime"), &EndTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("period"), &Period, Serializer);		
}

void UGetMetricsUrlRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ServiceName = Bag->GetStringField(TEXT("serviceName"));
	MetricName = Bag->GetStringField(TEXT("metricName"));
	UBeamJsonUtils::DeserializeOptional<int64>("startTime", Bag, StartTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("endTime", Bag, EndTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("period", Bag, Period, OuterOwner);
}



