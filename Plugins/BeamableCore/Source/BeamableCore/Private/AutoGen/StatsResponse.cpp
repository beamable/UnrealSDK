
#include "AutoGen/StatsResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UStatsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UStatsResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("stats"), Stats, Serializer);
}

void UStatsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("stats"), Stats, Serializer);		
}

void UStatsResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("stats")), Stats, OuterOwner);
}