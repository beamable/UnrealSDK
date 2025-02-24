

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/PlayerLobby/K2BeamNode_ApiRequest_DeleteLobbies.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/PlayerLobby/DeleteLobbiesRequest.h"
#include "BeamableCore/Public/AutoGen/ApiPlayersLobbiesDeletePlayerLobbyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteLobbies"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteLobbies::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteLobbies::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerLobbyApi, DeleteLobbies);
}

FName UK2BeamNode_ApiRequest_DeleteLobbies::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteLobbiesRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteLobbies::GetServiceName() const
{
	return TEXT("PlayerLobby");
}

FString UK2BeamNode_ApiRequest_DeleteLobbies::GetEndpointName() const
{
	return TEXT("DeleteLobbies");
}

UClass* UK2BeamNode_ApiRequest_DeleteLobbies::GetApiClass() const
{
	return UBeamPlayerLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteLobbies::GetRequestClass() const
{
	return UDeleteLobbiesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteLobbies::GetResponseClass() const
{
	return UApiPlayersLobbiesDeletePlayerLobbyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteLobbies::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteLobbiesSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteLobbies::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteLobbiesError");
}

FString UK2BeamNode_ApiRequest_DeleteLobbies::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteLobbiesComplete");
}

#undef LOCTEXT_NAMESPACE
