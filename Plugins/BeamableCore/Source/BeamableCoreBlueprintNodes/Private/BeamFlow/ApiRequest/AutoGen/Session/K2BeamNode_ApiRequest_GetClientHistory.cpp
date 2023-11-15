

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Session/K2BeamNode_ApiRequest_GetClientHistory.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamSessionApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/GetClientHistoryRequest.h"
#include "BeamableCore/Public/AutoGen/SessionClientHistoryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetClientHistory"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetClientHistory::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetClientHistory::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, GetClientHistory);
}

FName UK2BeamNode_ApiRequest_GetClientHistory::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetClientHistoryRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetClientHistory::GetServiceName() const
{
	return TEXT("Session");
}

FString UK2BeamNode_ApiRequest_GetClientHistory::GetEndpointName() const
{
	return TEXT("GetClientHistory");
}

UClass* UK2BeamNode_ApiRequest_GetClientHistory::GetApiClass() const
{
	return UBeamSessionApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetClientHistory::GetRequestClass() const
{
	return UGetClientHistoryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetClientHistory::GetResponseClass() const
{
	return USessionClientHistoryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetClientHistory::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetClientHistorySuccess");
}

FString UK2BeamNode_ApiRequest_GetClientHistory::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetClientHistoryError");
}

FString UK2BeamNode_ApiRequest_GetClientHistory::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetClientHistoryComplete");
}

#undef LOCTEXT_NAMESPACE
