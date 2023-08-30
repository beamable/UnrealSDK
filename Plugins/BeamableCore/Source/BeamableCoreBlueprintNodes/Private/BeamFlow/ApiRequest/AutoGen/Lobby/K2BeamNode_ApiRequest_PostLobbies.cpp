

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_PostLobbies.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/PostLobbiesRequest.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostLobbies"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostLobbies::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostLobbies::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, PostLobbies);
}

FName UK2BeamNode_ApiRequest_PostLobbies::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostLobbiesRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostLobbies::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_PostLobbies::GetEndpointName() const
{
	return TEXT("PostLobbies");
}

UClass* UK2BeamNode_ApiRequest_PostLobbies::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostLobbies::GetRequestClass() const
{
	return UPostLobbiesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostLobbies::GetResponseClass() const
{
	return ULobby::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostLobbies::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostLobbiesSuccess");
}

FString UK2BeamNode_ApiRequest_PostLobbies::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostLobbiesError");
}

FString UK2BeamNode_ApiRequest_PostLobbies::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostLobbiesComplete");
}

#undef LOCTEXT_NAMESPACE
