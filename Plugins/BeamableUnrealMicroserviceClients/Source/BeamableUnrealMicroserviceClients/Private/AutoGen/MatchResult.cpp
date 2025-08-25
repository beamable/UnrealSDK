
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MatchResult.h"
#include "Serialization/BeamJsonUtils.h"



void UMatchResult::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMatchResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<UPerPlayerMatchResult*>(TEXT("PerPlayerMatchResults"), PerPlayerMatchResults, Serializer);
}

void UMatchResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<UPerPlayerMatchResult*>(TEXT("PerPlayerMatchResults"), PerPlayerMatchResults, Serializer);		
}

void UMatchResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeMap<UPerPlayerMatchResult*>(TEXT("PerPlayerMatchResults"), Bag, PerPlayerMatchResults, OuterOwner);
}



