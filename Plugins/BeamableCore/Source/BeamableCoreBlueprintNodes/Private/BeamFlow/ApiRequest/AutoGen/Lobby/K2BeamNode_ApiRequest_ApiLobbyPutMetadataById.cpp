

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Lobby/K2BeamNode_ApiRequest_ApiLobbyPutMetadataById.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLobbyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/ApiLobbyPutMetadataByIdRequest.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiLobbyPutMetadataById"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiLobbyPutMetadataById::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiLobbyPutMetadataById::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLobbyApi, PutMetadata);
}

FName UK2BeamNode_ApiRequest_ApiLobbyPutMetadataById::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiLobbyPutMetadataByIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutMetadataById::GetServiceName() const
{
	return TEXT("Lobby");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutMetadataById::GetEndpointName() const
{
	return TEXT("PutMetadata");
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPutMetadataById::GetApiClass() const
{
	return UBeamLobbyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPutMetadataById::GetRequestClass() const
{
	return UApiLobbyPutMetadataByIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiLobbyPutMetadataById::GetResponseClass() const
{
	return ULobby::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutMetadataById::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiLobbyPutMetadataByIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutMetadataById::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiLobbyPutMetadataByIdError");
}

FString UK2BeamNode_ApiRequest_ApiLobbyPutMetadataById::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiLobbyPutMetadataByIdComplete");
}

#undef LOCTEXT_NAMESPACE
