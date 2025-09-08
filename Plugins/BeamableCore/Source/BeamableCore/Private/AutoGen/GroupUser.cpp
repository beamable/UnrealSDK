
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
	UBeamJsonUtils::SerializeOptional<TArray<UGroupUsersObjectInFlightMessage*>, UGroupUsersObjectInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);
}

void UGroupUser::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("updated"), Updated, Serializer);
	UBeamJsonUtils::SerializeUObject<UGroupMemberInfo*>("member", Member, Serializer);
	UBeamJsonUtils::SerializeArray<UGroupUserMember*>(TEXT("allGroups"), AllGroups, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupUsersObjectInFlightMessage*>, UGroupUsersObjectInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);		
}

void UGroupUser::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gamerTag"), Bag, GamerTag);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("updated"), Bag, Updated);
	UBeamJsonUtils::DeserializeUObject<UGroupMemberInfo*>("member", Bag, Member, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UGroupUserMember*>(TEXT("allGroups"), Bag, AllGroups, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupUsersObjectInFlightMessage*>, UGroupUsersObjectInFlightMessage*>("inFlight", Bag, InFlight, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>("scores", Bag, Scores, OuterOwner);
}



