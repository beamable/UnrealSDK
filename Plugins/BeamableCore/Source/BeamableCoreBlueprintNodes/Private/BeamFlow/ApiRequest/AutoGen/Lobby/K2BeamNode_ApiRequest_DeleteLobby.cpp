

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_DeleteLobby.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/DeleteLobbyRequest.h"
#include "BeamableCore/Public/AutoGen/Acknowledge.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteLobby"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteLobby::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteLobby::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, DeleteLobby);
}

FName UK2BeamNode_ApiRequest_DeleteLobby::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteLobbyRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteLobby::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_DeleteLobby::GetEndpointName() const
{
	return TEXT("DeleteLobby");
}

UClass* UK2BeamNode_ApiRequest_DeleteLobby::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteLobby::GetRequestClass() const
{
	return UDeleteLobbyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteLobby::GetResponseClass() const
{
	return UAcknowledge::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteLobby::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteLobbySuccess");
}

FString UK2BeamNode_ApiRequest_DeleteLobby::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteLobbyError");
}

FString UK2BeamNode_ApiRequest_DeleteLobby::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteLobbyComplete");
}

#undef LOCTEXT_NAMESPACE
