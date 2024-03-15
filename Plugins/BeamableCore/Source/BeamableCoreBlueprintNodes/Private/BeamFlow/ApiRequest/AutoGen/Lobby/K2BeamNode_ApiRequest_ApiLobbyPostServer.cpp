

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_ApiLobbyPostServer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/ApiLobbyPostServerRequest.h"
#include "BeamableCore/Public/AutoGen/ApiLobbiesServerPostLobbyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiLobbyPostServer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiLobbyPostServer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiLobbyPostServer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, PostServer);
}

FName UK2BeamNode_ApiRequest_ApiLobbyPostServer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiLobbyPostServerRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiLobbyPostServer::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPostServer::GetEndpointName() const
{
	return TEXT("PostServer");
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPostServer::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPostServer::GetRequestClass() const
{
	return UApiLobbyPostServerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPostServer::GetResponseClass() const
{
	return UApiLobbiesServerPostLobbyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiLobbyPostServer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiLobbyPostServerSuccess");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPostServer::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiLobbyPostServerError");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPostServer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiLobbyPostServerComplete");
}

#undef LOCTEXT_NAMESPACE
