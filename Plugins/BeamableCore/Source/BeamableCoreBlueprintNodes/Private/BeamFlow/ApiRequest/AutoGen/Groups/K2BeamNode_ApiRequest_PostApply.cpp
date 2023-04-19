

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_PostApply.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/PostApplyRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostApply"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostApply::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostApply::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, PostApply);
}

FName UK2BeamNode_ApiRequest_PostApply::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostApplyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostApply::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_PostApply::GetEndpointName() const
{
	return TEXT("PostApply");
}

UClass* UK2BeamNode_ApiRequest_PostApply::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostApply::GetRequestClass() const
{
	return UPostApplyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostApply::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostApply::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostApplySuccess");
}

FString UK2BeamNode_ApiRequest_PostApply::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostApplyError");
}

FString UK2BeamNode_ApiRequest_PostApply::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostApplyComplete");
}

#undef LOCTEXT_NAMESPACE
