

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Events/K2BeamNode_ApiRequest_PostApplyContent.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/PostApplyContentRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostApplyContent"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostApplyContent::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostApplyContent::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, PostApplyContent);
}

FName UK2BeamNode_ApiRequest_PostApplyContent::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostApplyContentRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostApplyContent::GetServiceName() const
{
	return TEXT("Events");
}

FString UK2BeamNode_ApiRequest_PostApplyContent::GetEndpointName() const
{
	return TEXT("PostApplyContent");
}

UClass* UK2BeamNode_ApiRequest_PostApplyContent::GetApiClass() const
{
	return UBeamEventsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostApplyContent::GetRequestClass() const
{
	return UPostApplyContentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostApplyContent::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostApplyContent::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostApplyContentSuccess");
}

FString UK2BeamNode_ApiRequest_PostApplyContent::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostApplyContentError");
}

FString UK2BeamNode_ApiRequest_PostApplyContent::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostApplyContentComplete");
}

#undef LOCTEXT_NAMESPACE
