

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/PlayerLobby/K2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/PlayerLobby/ApiPlayerLobbyGetLobbiesByPlayerIdRequest.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerLobbyApi, GetLobbies);
}

FName UK2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiPlayerLobbyGetLobbiesByPlayerIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId::GetServiceName() const
{
	return TEXT("PlayerLobby");
}

FString UK2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId::GetEndpointName() const
{
	return TEXT("GetLobbies");
}

UClass* UK2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId::GetApiClass() const
{
	return UBeamPlayerLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId::GetRequestClass() const
{
	return UApiPlayerLobbyGetLobbiesByPlayerIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId::GetResponseClass() const
{
	return ULobby::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiPlayerLobbyGetLobbiesByPlayerIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiPlayerLobbyGetLobbiesByPlayerIdError");
}

FString UK2BeamNode_ApiRequest_ApiPlayerLobbyGetLobbiesByPlayerId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiPlayerLobbyGetLobbiesByPlayerIdComplete");
}

#undef LOCTEXT_NAMESPACE
