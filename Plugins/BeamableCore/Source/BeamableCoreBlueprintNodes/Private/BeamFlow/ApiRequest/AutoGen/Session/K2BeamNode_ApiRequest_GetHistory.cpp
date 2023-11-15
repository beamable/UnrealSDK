

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Session/K2BeamNode_ApiRequest_GetHistory.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamSessionApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/GetHistoryRequest.h"
#include "BeamableCore/Public/AutoGen/SessionHistoryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetHistory"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetHistory::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetHistory::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, GetHistory);
}

FName UK2BeamNode_ApiRequest_GetHistory::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetHistoryRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetHistory::GetServiceName() const
{
	return TEXT("Session");
}

FString UK2BeamNode_ApiRequest_GetHistory::GetEndpointName() const
{
	return TEXT("GetHistory");
}

UClass* UK2BeamNode_ApiRequest_GetHistory::GetApiClass() const
{
	return UBeamSessionApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetHistory::GetRequestClass() const
{
	return UGetHistoryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetHistory::GetResponseClass() const
{
	return USessionHistoryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetHistory::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetHistorySuccess");
}

FString UK2BeamNode_ApiRequest_GetHistory::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetHistoryError");
}

FString UK2BeamNode_ApiRequest_GetHistory::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetHistoryComplete");
}

#undef LOCTEXT_NAMESPACE
