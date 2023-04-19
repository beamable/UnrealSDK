
#include "BeamableCore/Public/AutoGen/LeaderboardCohortSettings.h"
#include "Serialization/BeamJsonUtils.h"




void ULeaderboardCohortSettings::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<ULeaderboardCohort*>(TEXT("cohorts"), Cohorts, Serializer);
}

void ULeaderboardCohortSettings::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<ULeaderboardCohort*>(TEXT("cohorts"), Cohorts, Serializer);		
}

void ULeaderboardCohortSettings::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<ULeaderboardCohort*>(Bag->GetArrayField(TEXT("cohorts")), Cohorts, OuterOwner);
}



