

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_ApiLobbyPutMetadata.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/ApiLobbyPutMetadataRequest.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiLobbyPutMetadata"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiLobbyPutMetadata::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiLobbyPutMetadata::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, PutMetadata);
}

FName UK2BeamNode_ApiRequest_ApiLobbyPutMetadata::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiLobbyPutMetadataRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutMetadata::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutMetadata::GetEndpointName() const
{
	return TEXT("PutMetadata");
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPutMetadata::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPutMetadata::GetRequestClass() const
{
	return UApiLobbyPutMetadataRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPutMetadata::GetResponseClass() const
{
	return ULobby::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutMetadata::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiLobbyPutMetadataSuccess");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutMetadata::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiLobbyPutMetadataError");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutMetadata::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiLobbyPutMetadataComplete");
}

#undef LOCTEXT_NAMESPACE
