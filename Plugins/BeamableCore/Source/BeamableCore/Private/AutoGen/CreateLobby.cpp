
#include "BeamableCore/Public/AutoGen/CreateLobby.h"
#include "Serialization/BeamJsonUtils.h"




void UCreateLobby::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamLobbyRestriction>(TEXT("restriction"), &Restriction, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamContentId, FString>(TEXT("matchType"), &MatchType, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("passcodeLength"), &PasscodeLength, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxPlayers"), &MaxPlayers, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamTag>, FBeamTag>(TEXT("playerTags"), &PlayerTags, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("data"), &Data, Serializer);
}

void UCreateLobby::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamLobbyRestriction>(TEXT("restriction"), &Restriction, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamContentId, FString>(TEXT("matchType"), &MatchType, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("passcodeLength"), &PasscodeLength, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxPlayers"), &MaxPlayers, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamTag>, FBeamTag>(TEXT("playerTags"), &PlayerTags, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("data"), &Data, Serializer);		
}

void UCreateLobby::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<EBeamLobbyRestriction>("restriction", Bag, Restriction, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamContentId, FString>("matchType", Bag, MatchType, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("passcodeLength", Bag, PasscodeLength, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("maxPlayers", Bag, MaxPlayers, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamTag>, FBeamTag>("playerTags", Bag, PlayerTags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("data", Bag, Data, OuterOwner);
}



