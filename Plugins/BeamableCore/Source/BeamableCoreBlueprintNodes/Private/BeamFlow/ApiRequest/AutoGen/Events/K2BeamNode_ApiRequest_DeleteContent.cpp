

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Events/K2BeamNode_ApiRequest_DeleteContent.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/DeleteContentRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteContent"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteContent::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteContent::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, DeleteContent);
}

FName UK2BeamNode_ApiRequest_DeleteContent::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteContentRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteContent::GetServiceName() const
{
	return TEXT("Events");
}

FString UK2BeamNode_ApiRequest_DeleteContent::GetEndpointName() const
{
	return TEXT("DeleteContent");
}

UClass* UK2BeamNode_ApiRequest_DeleteContent::GetApiClass() const
{
	return UBeamEventsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteContent::GetRequestClass() const
{
	return UDeleteContentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteContent::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteContent::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteContentSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteContent::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteContentError");
}

FString UK2BeamNode_ApiRequest_DeleteContent::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteContentComplete");
}

#undef LOCTEXT_NAMESPACE
