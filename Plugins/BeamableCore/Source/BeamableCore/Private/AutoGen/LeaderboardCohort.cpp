
#include "BeamableCore/Public/AutoGen/LeaderboardCohort.h"
#include "Serialization/BeamJsonUtils.h"




void ULeaderboardCohort::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeArray<UPlayerStatRequirement*>(TEXT("statRequirements"), StatRequirements, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
}

void ULeaderboardCohort::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeArray<UPlayerStatRequirement*>(TEXT("statRequirements"), StatRequirements, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);		
}

void ULeaderboardCohort::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeArray<UPlayerStatRequirement*>(TEXT("statRequirements"), Bag, StatRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
}



