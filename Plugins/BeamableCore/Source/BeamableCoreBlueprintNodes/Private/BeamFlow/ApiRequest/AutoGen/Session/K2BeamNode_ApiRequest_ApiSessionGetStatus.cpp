

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Session/K2BeamNode_ApiRequest_ApiSessionGetStatus.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamSessionApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/ApiSessionGetStatusRequest.h"
#include "BeamableCore/Public/AutoGen/ApiSessionsStatusGetSessionResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiSessionGetStatus"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiSessionGetStatus::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiSessionGetStatus::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, ApiSessionGetStatus);
}

FName UK2BeamNode_ApiRequest_ApiSessionGetStatus::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiSessionGetStatusRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiSessionGetStatus::GetServiceName() const
{
	return TEXT("Session");
}

FString UK2BeamNode_ApiRequest_ApiSessionGetStatus::GetEndpointName() const
{
	return TEXT("ApiSessionGetStatus");
}

UClass* UK2BeamNode_ApiRequest_ApiSessionGetStatus::GetApiClass() const
{
	return UBeamSessionApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiSessionGetStatus::GetRequestClass() const
{
	return UApiSessionGetStatusRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiSessionGetStatus::GetResponseClass() const
{
	return UApiSessionsStatusGetSessionResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiSessionGetStatus::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiSessionGetStatusSuccess");
}

FString UK2BeamNode_ApiRequest_ApiSessionGetStatus::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiSessionGetStatusError");
}

FString UK2BeamNode_ApiRequest_ApiSessionGetStatus::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiSessionGetStatusComplete");
}

#undef LOCTEXT_NAMESPACE
