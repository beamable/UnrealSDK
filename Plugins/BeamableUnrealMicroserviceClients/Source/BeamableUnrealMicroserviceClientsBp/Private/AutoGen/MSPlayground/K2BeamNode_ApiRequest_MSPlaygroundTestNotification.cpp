

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/MSPlayground/K2BeamNode_ApiRequest_MSPlaygroundTestNotification.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamMSPlaygroundApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/MSPlayground/MSPlaygroundTestNotificationRequest.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_MSPlaygroundTestNotification"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_MSPlaygroundTestNotification::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMSPlaygroundApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_MSPlaygroundTestNotification::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMSPlaygroundApi, TestNotification);
}

FName UK2BeamNode_ApiRequest_MSPlaygroundTestNotification::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UMSPlaygroundTestNotificationRequest, Make);
}

FString UK2BeamNode_ApiRequest_MSPlaygroundTestNotification::GetServiceName() const
{
	return TEXT("MSPlayground");
}

FString UK2BeamNode_ApiRequest_MSPlaygroundTestNotification::GetEndpointName() const
{
	return TEXT("TestNotification");
}

UClass* UK2BeamNode_ApiRequest_MSPlaygroundTestNotification::GetApiClass() const
{
	return UBeamMSPlaygroundApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_MSPlaygroundTestNotification::GetRequestClass() const
{
	return UMSPlaygroundTestNotificationRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_MSPlaygroundTestNotification::GetResponseClass() const
{
	return UBeamPlainTextResponseBody::StaticClass();
}

FString UK2BeamNode_ApiRequest_MSPlaygroundTestNotification::GetRequestSuccessDelegateName() const
{
	return TEXT("OnMSPlaygroundTestNotificationSuccess");
}

FString UK2BeamNode_ApiRequest_MSPlaygroundTestNotification::GetRequestErrorDelegateName() const
{
	return TEXT("OnMSPlaygroundTestNotificationError");
}

FString UK2BeamNode_ApiRequest_MSPlaygroundTestNotification::GetRequestCompleteDelegateName() const
{
	return TEXT("OnMSPlaygroundTestNotificationComplete");
}

#undef LOCTEXT_NAMESPACE
