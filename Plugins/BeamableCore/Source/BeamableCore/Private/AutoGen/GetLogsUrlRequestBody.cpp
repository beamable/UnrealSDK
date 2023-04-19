
#include "BeamableCore/Public/AutoGen/GetLogsUrlRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetLogsUrlRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("nextToken"), &NextToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("filter"), &Filter, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("endTime"), &EndTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
}

void UGetLogsUrlRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("nextToken"), &NextToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("filter"), &Filter, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("endTime"), &EndTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);		
}

void UGetLogsUrlRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ServiceName = Bag->GetStringField(TEXT("serviceName"));
	UBeamJsonUtils::DeserializeOptional<int64>("startTime", Bag, StartTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("nextToken", Bag, NextToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("filter", Bag, Filter, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("endTime", Bag, EndTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
}



