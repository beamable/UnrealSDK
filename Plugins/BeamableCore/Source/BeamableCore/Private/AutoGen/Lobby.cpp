
#include "BeamableCore/Public/AutoGen/Lobby.h"
#include "Serialization/BeamJsonUtils.h"



void ULobby::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void ULobby::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lobbyId"), &LobbyId, Serializer);
	UBeamJsonUtils::SerializeOptional<UMatchType*>(TEXT("matchType"), &MatchType, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("host"), &Host, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("passcode"), &Passcode, Serializer);
	UBeamJsonUtils::SerializeOptional<ELobbyRestriction>(TEXT("restriction"), &Restriction, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxPlayers"), &MaxPlayers, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<ULobbyPlayer*>, ULobbyPlayer*>(TEXT("players"), &Players, Serializer);
}

void ULobby::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lobbyId"), &LobbyId, Serializer);
	UBeamJsonUtils::SerializeOptional<UMatchType*>(TEXT("matchType"), &MatchType, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("host"), &Host, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("passcode"), &Passcode, Serializer);
	UBeamJsonUtils::SerializeOptional<ELobbyRestriction>(TEXT("restriction"), &Restriction, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxPlayers"), &MaxPlayers, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<ULobbyPlayer*>, ULobbyPlayer*>(TEXT("players"), &Players, Serializer);		
}

void ULobby::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("lobbyId", Bag, LobbyId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UMatchType*>("matchType", Bag, MatchType, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("created", Bag, Created, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("host", Bag, Host, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("passcode", Bag, Passcode, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<ELobbyRestriction>("restriction", Bag, Restriction, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("maxPlayers", Bag, MaxPlayers, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<ULobbyPlayer*>, ULobbyPlayer*>("players", Bag, Players, OuterOwner);
}



