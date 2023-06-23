

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_PutLobby.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/PutLobbyRequest.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutLobby"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutLobby::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutLobby::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, PutLobby);
}

FName UK2BeamNode_ApiRequest_PutLobby::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutLobbyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutLobby::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_PutLobby::GetEndpointName() const
{
	return TEXT("PutLobby");
}

UClass* UK2BeamNode_ApiRequest_PutLobby::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutLobby::GetRequestClass() const
{
	return UPutLobbyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutLobby::GetResponseClass() const
{
	return ULobby::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutLobby::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutLobbySuccess");
}

FString UK2BeamNode_ApiRequest_PutLobby::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutLobbyError");
}

FString UK2BeamNode_ApiRequest_PutLobby::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutLobbyComplete");
}

#undef LOCTEXT_NAMESPACE
