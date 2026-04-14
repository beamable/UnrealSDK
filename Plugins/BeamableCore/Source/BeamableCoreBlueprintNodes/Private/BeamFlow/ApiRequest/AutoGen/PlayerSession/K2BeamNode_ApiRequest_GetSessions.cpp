

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/PlayerSession/K2BeamNode_ApiRequest_GetSessions.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerSessionApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/PlayerSession/GetSessionsRequest.h"
#include "BeamableCore/Public/AutoGen/SessionHistoryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetSessions"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetSessions::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerSessionApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetSessions::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerSessionApi, GetSessions);
}

FName UK2BeamNode_ApiRequest_GetSessions::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetSessionsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetSessions::GetServiceName() const
{
	return TEXT("PlayerSession");
}

FString UK2BeamNode_ApiRequest_GetSessions::GetEndpointName() const
{
	return TEXT("GetSessions");
}

UClass* UK2BeamNode_ApiRequest_GetSessions::GetApiClass() const
{
	return UBeamPlayerSessionApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSessions::GetRequestClass() const
{
	return UGetSessionsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSessions::GetResponseClass() const
{
	return USessionHistoryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetSessions::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetSessionsSuccess");
}

FString UK2BeamNode_ApiRequest_GetSessions::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetSessionsError");
}

FString UK2BeamNode_ApiRequest_GetSessions::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetSessionsComplete");
}

#undef LOCTEXT_NAMESPACE
