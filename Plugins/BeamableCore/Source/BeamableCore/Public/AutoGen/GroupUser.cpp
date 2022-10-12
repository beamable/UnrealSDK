
#include "AutoGen/GroupUser.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UGroupUser ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
	UBeamJsonUtils::SerializeArray<UGroupUserMember*>(TEXT("allGroups"), AllGroups, Serializer);
	Serializer->WriteValue(TEXT("updated"), Updated);
	UBeamJsonUtils::SerializeMap<FArrayOfString>(TEXT("member"), Member, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);
}

void UGroupUser::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
	UBeamJsonUtils::SerializeArray<UGroupUserMember*>(TEXT("allGroups"), AllGroups, Serializer);
	Serializer->WriteValue(TEXT("updated"), Updated);
	UBeamJsonUtils::SerializeMap<FArrayOfString>(TEXT("member"), Member, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);		
}

void UGroupUser ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>("inFlight", Bag, InFlight, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
	UBeamJsonUtils::DeserializeArray<UGroupUserMember*>(Bag->GetArrayField(TEXT("allGroups")), AllGroups, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("updated")), Updated);
	UBeamJsonUtils::DeserializeMap<FArrayOfString>(Bag->GetObjectField(TEXT("member")), Member, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>("scores", Bag, Scores, OuterOwner);
}