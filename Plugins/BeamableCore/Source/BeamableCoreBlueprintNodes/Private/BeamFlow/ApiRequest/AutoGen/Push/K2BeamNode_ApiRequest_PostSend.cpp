

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Push/K2BeamNode_ApiRequest_PostSend.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPushApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Push/PostSendRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyRsp.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSend"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSend::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPushApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSend::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPushApi, PostSend);
}

FName UK2BeamNode_ApiRequest_PostSend::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSendRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSend::GetServiceName() const
{
	return TEXT("Push");
}

FString UK2BeamNode_ApiRequest_PostSend::GetEndpointName() const
{
	return TEXT("PostSend");
}

UClass* UK2BeamNode_ApiRequest_PostSend::GetApiClass() const
{
	return UBeamPushApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSend::GetRequestClass() const
{
	return UPostSendRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSend::GetResponseClass() const
{
	return UEmptyRsp::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSend::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSendSuccess");
}

FString UK2BeamNode_ApiRequest_PostSend::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSendError");
}

FString UK2BeamNode_ApiRequest_PostSend::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSendComplete");
}

#undef LOCTEXT_NAMESPACE
