

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_DeleteSubscribe.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/DeleteSubscribeRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteSubscribe"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteSubscribe::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteSubscribe::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, DeleteSubscribe);
}

FName UK2BeamNode_ApiRequest_DeleteSubscribe::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteSubscribeRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteSubscribe::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_DeleteSubscribe::GetEndpointName() const
{
	return TEXT("DeleteSubscribe");
}

UClass* UK2BeamNode_ApiRequest_DeleteSubscribe::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteSubscribe::GetRequestClass() const
{
	return UDeleteSubscribeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteSubscribe::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteSubscribe::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteSubscribeSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteSubscribe::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteSubscribeError");
}

FString UK2BeamNode_ApiRequest_DeleteSubscribe::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteSubscribeComplete");
}

#undef LOCTEXT_NAMESPACE
