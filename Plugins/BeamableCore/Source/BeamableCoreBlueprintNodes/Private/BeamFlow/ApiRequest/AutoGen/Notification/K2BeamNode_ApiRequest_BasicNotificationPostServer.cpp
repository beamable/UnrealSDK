

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Notification/K2BeamNode_ApiRequest_BasicNotificationPostServer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamNotificationApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Notification/BasicNotificationPostServerRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicNotificationPostServer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicNotificationPostServer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicNotificationPostServer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, PostServer);
}

FName UK2BeamNode_ApiRequest_BasicNotificationPostServer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicNotificationPostServerRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicNotificationPostServer::GetServiceName() const
{
	return TEXT("Notification");
}

FString UK2BeamNode_ApiRequest_BasicNotificationPostServer::GetEndpointName() const
{
	return TEXT("PostServer");
}

UClass* UK2BeamNode_ApiRequest_BasicNotificationPostServer::GetApiClass() const
{
	return UBeamNotificationApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicNotificationPostServer::GetRequestClass() const
{
	return UBasicNotificationPostServerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicNotificationPostServer::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicNotificationPostServer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicNotificationPostServerSuccess");
}

FString UK2BeamNode_ApiRequest_BasicNotificationPostServer::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicNotificationPostServerError");
}

FString UK2BeamNode_ApiRequest_BasicNotificationPostServer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicNotificationPostServerComplete");
}

#undef LOCTEXT_NAMESPACE
