
#include "BeamableCore/Public/AutoGen/Member.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMember::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("role"), Role);
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canDemote"), &bCanDemote, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canKick"), &bCanKick, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canPromote"), &bCanPromote, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);
}

void UMember::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("role"), Role);
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canDemote"), &bCanDemote, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canKick"), &bCanKick, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canPromote"), &bCanPromote, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);		
}

void UMember::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Role = Bag->GetStringField(TEXT("role"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
	UBeamJsonUtils::DeserializeOptional<bool>("canDemote", Bag, bCanDemote, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canKick", Bag, bCanKick, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canPromote", Bag, bCanPromote, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>("scores", Bag, Scores, OuterOwner);
}



