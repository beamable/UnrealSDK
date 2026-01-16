

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_ApiLobbyPutTagsById.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/ApiLobbyPutTagsByIdRequest.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiLobbyPutTagsById"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiLobbyPutTagsById::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiLobbyPutTagsById::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, PutTags);
}

FName UK2BeamNode_ApiRequest_ApiLobbyPutTagsById::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiLobbyPutTagsByIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutTagsById::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutTagsById::GetEndpointName() const
{
	return TEXT("PutTags");
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPutTagsById::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPutTagsById::GetRequestClass() const
{
	return UApiLobbyPutTagsByIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPutTagsById::GetResponseClass() const
{
	return ULobby::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutTagsById::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiLobbyPutTagsByIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutTagsById::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiLobbyPutTagsByIdError");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutTagsById::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiLobbyPutTagsByIdComplete");
}

#undef LOCTEXT_NAMESPACE
