

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_GetLobbies.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/GetLobbiesRequest.h"
#include "BeamableCore/Public/AutoGen/LobbyQueryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetLobbies"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetLobbies::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetLobbies::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetLobbies);
}

FName UK2BeamNode_ApiRequest_GetLobbies::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetLobbiesRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetLobbies::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_GetLobbies::GetEndpointName() const
{
	return TEXT("GetLobbies");
}

UClass* UK2BeamNode_ApiRequest_GetLobbies::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetLobbies::GetRequestClass() const
{
	return UGetLobbiesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetLobbies::GetResponseClass() const
{
	return ULobbyQueryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetLobbies::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetLobbiesSuccess");
}

FString UK2BeamNode_ApiRequest_GetLobbies::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetLobbiesError");
}

FString UK2BeamNode_ApiRequest_GetLobbies::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetLobbiesComplete");
}

#undef LOCTEXT_NAMESPACE
