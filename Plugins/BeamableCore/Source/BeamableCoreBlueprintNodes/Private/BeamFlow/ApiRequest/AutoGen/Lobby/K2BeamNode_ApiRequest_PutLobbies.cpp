

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_PutLobbies.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/PutLobbiesRequest.h"
#include "BeamableCore/Public/AutoGen/SetLobbyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutLobbies"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutLobbies::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutLobbies::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, PutLobbies);
}

FName UK2BeamNode_ApiRequest_PutLobbies::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutLobbiesRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutLobbies::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_PutLobbies::GetEndpointName() const
{
	return TEXT("PutLobbies");
}

UClass* UK2BeamNode_ApiRequest_PutLobbies::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutLobbies::GetRequestClass() const
{
	return UPutLobbiesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutLobbies::GetResponseClass() const
{
	return USetLobbyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutLobbies::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutLobbiesSuccess");
}

FString UK2BeamNode_ApiRequest_PutLobbies::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutLobbiesError");
}

FString UK2BeamNode_ApiRequest_PutLobbies::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutLobbiesComplete");
}

#undef LOCTEXT_NAMESPACE
