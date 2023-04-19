

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_BasicContentGetContent.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/BasicContentGetContentRequest.h"
#include "BeamableCore/Public/AutoGen/ContentOrText.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicContentGetContent"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicContentGetContent::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicContentGetContent::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetContent);
}

FName UK2BeamNode_ApiRequest_BasicContentGetContent::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicContentGetContentRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicContentGetContent::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_BasicContentGetContent::GetEndpointName() const
{
	return TEXT("GetContent");
}

UClass* UK2BeamNode_ApiRequest_BasicContentGetContent::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicContentGetContent::GetRequestClass() const
{
	return UBasicContentGetContentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicContentGetContent::GetResponseClass() const
{
	return UContentOrText::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicContentGetContent::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicContentGetContentSuccess");
}

FString UK2BeamNode_ApiRequest_BasicContentGetContent::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicContentGetContentError");
}

FString UK2BeamNode_ApiRequest_BasicContentGetContent::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicContentGetContentComplete");
}

#undef LOCTEXT_NAMESPACE
