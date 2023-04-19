

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_PostContent.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostContentRequest.h"
#include "BeamableCore/Public/AutoGen/SaveContentResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostContent"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostContent::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostContent::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, PostContent);
}

FName UK2BeamNode_ApiRequest_PostContent::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostContentRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostContent::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_PostContent::GetEndpointName() const
{
	return TEXT("PostContent");
}

UClass* UK2BeamNode_ApiRequest_PostContent::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostContent::GetRequestClass() const
{
	return UPostContentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostContent::GetResponseClass() const
{
	return USaveContentResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostContent::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostContentSuccess");
}

FString UK2BeamNode_ApiRequest_PostContent::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostContentError");
}

FString UK2BeamNode_ApiRequest_PostContent::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostContentComplete");
}

#undef LOCTEXT_NAMESPACE
