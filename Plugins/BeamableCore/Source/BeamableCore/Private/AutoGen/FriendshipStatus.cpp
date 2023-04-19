
#include "BeamableCore/Public/AutoGen/FriendshipStatus.h"
#include "Serialization/BeamJsonUtils.h"



void UFriendshipStatus::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UFriendshipStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isBlocked"), bIsBlocked);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("friendId"), &FriendId, Serializer);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("playerId"), &PlayerId, Serializer);
}

void UFriendshipStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isBlocked"), bIsBlocked);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("friendId"), &FriendId, Serializer);
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("playerId"), &PlayerId, Serializer);		
}

void UFriendshipStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bIsBlocked = Bag->GetBoolField(TEXT("isBlocked"));
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("friendId")), FriendId, OuterOwner);
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("playerId")), PlayerId, OuterOwner);
}



