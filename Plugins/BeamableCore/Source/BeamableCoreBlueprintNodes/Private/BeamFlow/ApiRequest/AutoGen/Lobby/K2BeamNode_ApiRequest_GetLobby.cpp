

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_GetLobby.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/GetLobbyRequest.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetLobby"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetLobby::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetLobby::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetLobby);
}

FName UK2BeamNode_ApiRequest_GetLobby::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetLobbyRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetLobby::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_GetLobby::GetEndpointName() const
{
	return TEXT("GetLobby");
}

UClass* UK2BeamNode_ApiRequest_GetLobby::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetLobby::GetRequestClass() const
{
	return UGetLobbyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetLobby::GetResponseClass() const
{
	return ULobby::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetLobby::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetLobbySuccess");
}

FString UK2BeamNode_ApiRequest_GetLobby::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetLobbyError");
}

FString UK2BeamNode_ApiRequest_GetLobby::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetLobbyComplete");
}

#undef LOCTEXT_NAMESPACE
