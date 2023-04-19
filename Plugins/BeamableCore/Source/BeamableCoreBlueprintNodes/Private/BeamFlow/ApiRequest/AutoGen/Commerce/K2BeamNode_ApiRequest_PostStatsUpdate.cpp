

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_PostStatsUpdate.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/PostStatsUpdateRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostStatsUpdate"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostStatsUpdate::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostStatsUpdate::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, PostStatsUpdate);
}

FName UK2BeamNode_ApiRequest_PostStatsUpdate::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostStatsUpdateRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostStatsUpdate::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_PostStatsUpdate::GetEndpointName() const
{
	return TEXT("PostStatsUpdate");
}

UClass* UK2BeamNode_ApiRequest_PostStatsUpdate::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostStatsUpdate::GetRequestClass() const
{
	return UPostStatsUpdateRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostStatsUpdate::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostStatsUpdate::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostStatsUpdateSuccess");
}

FString UK2BeamNode_ApiRequest_PostStatsUpdate::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostStatsUpdateError");
}

FString UK2BeamNode_ApiRequest_PostStatsUpdate::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostStatsUpdateComplete");
}

#undef LOCTEXT_NAMESPACE
