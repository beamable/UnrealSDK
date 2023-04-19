

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_PostText.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostTextRequest.h"
#include "BeamableCore/Public/AutoGen/SaveTextResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostText"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostText::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostText::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, PostText);
}

FName UK2BeamNode_ApiRequest_PostText::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTextRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostText::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_PostText::GetEndpointName() const
{
	return TEXT("PostText");
}

UClass* UK2BeamNode_ApiRequest_PostText::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostText::GetRequestClass() const
{
	return UPostTextRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostText::GetResponseClass() const
{
	return USaveTextResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostText::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTextSuccess");
}

FString UK2BeamNode_ApiRequest_PostText::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTextError");
}

FString UK2BeamNode_ApiRequest_PostText::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTextComplete");
}

#undef LOCTEXT_NAMESPACE
