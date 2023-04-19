

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Notification/K2BeamNode_ApiRequest_GetNotification.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamNotificationApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Notification/GetNotificationRequest.h"
#include "BeamableCore/Public/AutoGen/SubscriberDetailsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetNotification"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetNotification::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetNotification::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, GetNotification);
}

FName UK2BeamNode_ApiRequest_GetNotification::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetNotificationRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetNotification::GetServiceName() const
{
	return TEXT("Notification");
}

FString UK2BeamNode_ApiRequest_GetNotification::GetEndpointName() const
{
	return TEXT("GetNotification");
}

UClass* UK2BeamNode_ApiRequest_GetNotification::GetApiClass() const
{
	return UBeamNotificationApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetNotification::GetRequestClass() const
{
	return UGetNotificationRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetNotification::GetResponseClass() const
{
	return USubscriberDetailsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetNotification::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetNotificationSuccess");
}

FString UK2BeamNode_ApiRequest_GetNotification::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetNotificationError");
}

FString UK2BeamNode_ApiRequest_GetNotification::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetNotificationComplete");
}

#undef LOCTEXT_NAMESPACE
