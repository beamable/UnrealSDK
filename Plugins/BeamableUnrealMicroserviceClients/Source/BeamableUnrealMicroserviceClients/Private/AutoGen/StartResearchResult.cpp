
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/StartResearchResult.h"

#include "Misc/DefaultValueHelper.h"


void UStartResearchResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UStartResearchResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("startedAtUtcSeconds"), StartedAtUtcSeconds, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("pointsSpent"), PointsSpent, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);
}

void UStartResearchResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("startedAtUtcSeconds"), StartedAtUtcSeconds, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("pointsSpent"), PointsSpent, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("success"), bSuccess, Serializer);		
}

void UStartResearchResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("startedAtUtcSeconds"), Bag, StartedAtUtcSeconds);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("pointsSpent"), Bag, PointsSpent);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("success"), Bag, bSuccess);
}



