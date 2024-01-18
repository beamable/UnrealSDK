

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Notification/K2BeamNode_ApiRequest_PostChannel.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamNotificationApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Notification/PostChannelRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostChannel"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostChannel::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostChannel::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, PostChannel);
}

FName UK2BeamNode_ApiRequest_PostChannel::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostChannelRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostChannel::GetServiceName() const
{
	return TEXT("Notification");
}

FString UK2BeamNode_ApiRequest_PostChannel::GetEndpointName() const
{
	return TEXT("PostChannel");
}

UClass* UK2BeamNode_ApiRequest_PostChannel::GetApiClass() const
{
	return UBeamNotificationApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostChannel::GetRequestClass() const
{
	return UPostChannelRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostChannel::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostChannel::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostChannelSuccess");
}

FString UK2BeamNode_ApiRequest_PostChannel::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostChannelError");
}

FString UK2BeamNode_ApiRequest_PostChannel::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostChannelComplete");
}

#undef LOCTEXT_NAMESPACE
