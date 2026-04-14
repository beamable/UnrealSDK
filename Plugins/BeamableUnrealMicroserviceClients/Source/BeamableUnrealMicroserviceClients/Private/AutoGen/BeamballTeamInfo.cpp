
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballTeamInfo.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamballTeamInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("TeamName"), TeamName, Serializer);
	UBeamJsonUtils::SerializeArray<UBeamballPlayerInfo*>(TEXT("Players"), Players, Serializer);
}

void UBeamballTeamInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("TeamName"), TeamName, Serializer);
	UBeamJsonUtils::SerializeArray<UBeamballPlayerInfo*>(TEXT("Players"), Players, Serializer);		
}

void UBeamballTeamInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("TeamName"), Bag, TeamName);
	UBeamJsonUtils::DeserializeArray<UBeamballPlayerInfo*>(TEXT("Players"), Bag, Players, OuterOwner);
}



