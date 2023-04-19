
#include "BeamableCore/Public/AutoGen/LeaderboardCohort.h"
#include "Serialization/BeamJsonUtils.h"




void ULeaderboardCohort::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UPlayerStatRequirement*>(TEXT("statRequirements"), StatRequirements, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
}

void ULeaderboardCohort::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UPlayerStatRequirement*>(TEXT("statRequirements"), StatRequirements, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);		
}

void ULeaderboardCohort::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	UBeamJsonUtils::DeserializeArray<UPlayerStatRequirement*>(Bag->GetArrayField(TEXT("statRequirements")), StatRequirements, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
}



