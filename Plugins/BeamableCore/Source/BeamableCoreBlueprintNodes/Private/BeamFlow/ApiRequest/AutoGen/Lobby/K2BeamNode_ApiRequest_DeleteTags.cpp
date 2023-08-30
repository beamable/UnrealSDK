

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_DeleteTags.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/DeleteTagsRequest.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteTags"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteTags::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteTags::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, DeleteTags);
}

FName UK2BeamNode_ApiRequest_DeleteTags::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteTagsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteTags::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_DeleteTags::GetEndpointName() const
{
	return TEXT("DeleteTags");
}

UClass* UK2BeamNode_ApiRequest_DeleteTags::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteTags::GetRequestClass() const
{
	return UDeleteTagsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteTags::GetResponseClass() const
{
	return ULobby::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteTags::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteTagsSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteTags::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteTagsError");
}

FString UK2BeamNode_ApiRequest_DeleteTags::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteTagsComplete");
}

#undef LOCTEXT_NAMESPACE
