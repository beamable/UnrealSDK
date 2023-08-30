
#include "BeamableCore/Public/AutoGen/JoinLobbyByPasscode.h"
#include "Serialization/BeamJsonUtils.h"




void UJoinLobbyByPasscode::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("passcode"), &Passcode, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTag*>, UTag*>(TEXT("tags"), &Tags, Serializer);
}

void UJoinLobbyByPasscode::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("passcode"), &Passcode, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTag*>, UTag*>(TEXT("tags"), &Tags, Serializer);		
}

void UJoinLobbyByPasscode::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("passcode", Bag, Passcode, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UTag*>, UTag*>("tags", Bag, Tags, OuterOwner);
}



