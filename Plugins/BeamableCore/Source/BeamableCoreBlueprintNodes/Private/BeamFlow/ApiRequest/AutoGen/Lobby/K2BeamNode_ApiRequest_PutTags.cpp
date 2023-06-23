

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_PutTags.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/PutTagsRequest.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutTags"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutTags::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutTags::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, PutTags);
}

FName UK2BeamNode_ApiRequest_PutTags::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutTagsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutTags::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_PutTags::GetEndpointName() const
{
	return TEXT("PutTags");
}

UClass* UK2BeamNode_ApiRequest_PutTags::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutTags::GetRequestClass() const
{
	return UPutTagsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutTags::GetResponseClass() const
{
	return ULobby::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutTags::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutTagsSuccess");
}

FString UK2BeamNode_ApiRequest_PutTags::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutTagsError");
}

FString UK2BeamNode_ApiRequest_PutTags::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutTagsComplete");
}

#undef LOCTEXT_NAMESPACE
