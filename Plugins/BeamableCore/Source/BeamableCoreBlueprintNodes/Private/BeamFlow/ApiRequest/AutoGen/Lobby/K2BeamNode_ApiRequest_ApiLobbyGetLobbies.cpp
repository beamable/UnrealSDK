

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_ApiLobbyGetLobbies.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/ApiLobbyGetLobbiesRequest.h"
#include "BeamableCore/Public/AutoGen/LobbyQueryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiLobbyGetLobbies"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiLobbyGetLobbies::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiLobbyGetLobbies::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetLobbies);
}

FName UK2BeamNode_ApiRequest_ApiLobbyGetLobbies::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiLobbyGetLobbiesRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiLobbyGetLobbies::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_ApiLobbyGetLobbies::GetEndpointName() const
{
	return TEXT("GetLobbies");
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyGetLobbies::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyGetLobbies::GetRequestClass() const
{
	return UApiLobbyGetLobbiesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyGetLobbies::GetResponseClass() const
{
	return ULobbyQueryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiLobbyGetLobbies::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiLobbyGetLobbiesSuccess");
}

FString UK2BeamNode_ApiRequest_ApiLobbyGetLobbies::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiLobbyGetLobbiesError");
}

FString UK2BeamNode_ApiRequest_ApiLobbyGetLobbies::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiLobbyGetLobbiesComplete");
}

#undef LOCTEXT_NAMESPACE
