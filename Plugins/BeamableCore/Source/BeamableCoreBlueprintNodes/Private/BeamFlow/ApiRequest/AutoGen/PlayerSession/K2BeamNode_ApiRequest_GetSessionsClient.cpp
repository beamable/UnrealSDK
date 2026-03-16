

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/PlayerSession/K2BeamNode_ApiRequest_GetSessionsClient.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerSessionApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/PlayerSession/GetSessionsClientRequest.h"
#include "BeamableCore/Public/AutoGen/SessionClientHistoryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetSessionsClient"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetSessionsClient::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerSessionApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetSessionsClient::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerSessionApi, GetSessionsClient);
}

FName UK2BeamNode_ApiRequest_GetSessionsClient::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetSessionsClientRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetSessionsClient::GetServiceName() const
{
	return TEXT("PlayerSession");
}

FString UK2BeamNode_ApiRequest_GetSessionsClient::GetEndpointName() const
{
	return TEXT("GetSessionsClient");
}

UClass* UK2BeamNode_ApiRequest_GetSessionsClient::GetApiClass() const
{
	return UBeamPlayerSessionApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSessionsClient::GetRequestClass() const
{
	return UGetSessionsClientRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSessionsClient::GetResponseClass() const
{
	return USessionClientHistoryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetSessionsClient::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetSessionsClientSuccess");
}

FString UK2BeamNode_ApiRequest_GetSessionsClient::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetSessionsClientError");
}

FString UK2BeamNode_ApiRequest_GetSessionsClient::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetSessionsClientComplete");
}

#undef LOCTEXT_NAMESPACE
