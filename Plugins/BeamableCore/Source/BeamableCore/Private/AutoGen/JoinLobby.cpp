
#include "BeamableCore/Public/AutoGen/JoinLobby.h"
#include "Serialization/BeamJsonUtils.h"




void UJoinLobby::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("passcode"), &Passcode, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamTag>, FBeamTag>(TEXT("tags"), &Tags, Serializer);
}

void UJoinLobby::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("passcode"), &Passcode, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamTag>, FBeamTag>(TEXT("tags"), &Tags, Serializer);		
}

void UJoinLobby::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("passcode", Bag, Passcode, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamTag>, FBeamTag>("tags", Bag, Tags, OuterOwner);
}



