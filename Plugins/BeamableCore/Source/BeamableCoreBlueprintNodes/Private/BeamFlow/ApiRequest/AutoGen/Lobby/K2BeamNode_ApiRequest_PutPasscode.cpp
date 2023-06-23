

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_PutPasscode.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/PutPasscodeRequest.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutPasscode"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutPasscode::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutPasscode::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, PutPasscode);
}

FName UK2BeamNode_ApiRequest_PutPasscode::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutPasscodeRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutPasscode::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_PutPasscode::GetEndpointName() const
{
	return TEXT("PutPasscode");
}

UClass* UK2BeamNode_ApiRequest_PutPasscode::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPasscode::GetRequestClass() const
{
	return UPutPasscodeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPasscode::GetResponseClass() const
{
	return ULobby::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutPasscode::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutPasscodeSuccess");
}

FString UK2BeamNode_ApiRequest_PutPasscode::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutPasscodeError");
}

FString UK2BeamNode_ApiRequest_PutPasscode::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutPasscodeComplete");
}

#undef LOCTEXT_NAMESPACE
