

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_DeleteStatus.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/DeleteStatusRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteStatus"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteStatus::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteStatus::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, DeleteStatus);
}

FName UK2BeamNode_ApiRequest_DeleteStatus::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteStatusRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteStatus::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_DeleteStatus::GetEndpointName() const
{
	return TEXT("DeleteStatus");
}

UClass* UK2BeamNode_ApiRequest_DeleteStatus::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteStatus::GetRequestClass() const
{
	return UDeleteStatusRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteStatus::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteStatus::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteStatusSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteStatus::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteStatusError");
}

FString UK2BeamNode_ApiRequest_DeleteStatus::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteStatusComplete");
}

#undef LOCTEXT_NAMESPACE
