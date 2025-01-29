

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_ApiLobbyPostServerById.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/ApiLobbyPostServerByIdRequest.h"
#include "BeamableCore/Public/AutoGen/ApiLobbiesServerPostLobbyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiLobbyPostServerById"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiLobbyPostServerById::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiLobbyPostServerById::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, PostServer);
}

FName UK2BeamNode_ApiRequest_ApiLobbyPostServerById::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiLobbyPostServerByIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiLobbyPostServerById::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPostServerById::GetEndpointName() const
{
	return TEXT("PostServer");
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPostServerById::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPostServerById::GetRequestClass() const
{
	return UApiLobbyPostServerByIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPostServerById::GetResponseClass() const
{
	return UApiLobbiesServerPostLobbyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiLobbyPostServerById::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiLobbyPostServerByIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPostServerById::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiLobbyPostServerByIdError");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPostServerById::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiLobbyPostServerByIdComplete");
}

#undef LOCTEXT_NAMESPACE
