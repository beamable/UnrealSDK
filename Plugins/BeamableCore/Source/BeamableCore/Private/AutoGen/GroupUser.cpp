
#include "BeamableCore/Public/AutoGen/GroupUser.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UGroupUser::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGroupUser::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("updated"), Updated, Serializer);
	UBeamJsonUtils::SerializeUObject<UGroupMemberInfo*>("member", Member, Serializer);
	UBeamJsonUtils::SerializeArray<UGroupUserMember*>(TEXT("allGroups"), AllGroups, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);
}

void UGroupUser::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("updated"), Updated, Serializer);
	UBeamJsonUtils::SerializeUObject<UGroupMemberInfo*>("member", Member, Serializer);
	UBeamJsonUtils::SerializeArray<UGroupUserMember*>(TEXT("allGroups"), AllGroups, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);		
}

void UGroupUser::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("updated")), Updated);
	UBeamJsonUtils::DeserializeUObject<UGroupMemberInfo*>("member", Bag, Member, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UGroupUserMember*>(Bag->GetArrayField(TEXT("allGroups")), AllGroups, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>("inFlight", Bag, InFlight, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>("scores", Bag, Scores, OuterOwner);
}



