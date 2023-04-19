

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Notification/K2BeamNode_ApiRequest_PostServer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamNotificationApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Notification/PostServerRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostServer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostServer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostServer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, PostServer);
}

FName UK2BeamNode_ApiRequest_PostServer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostServerRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostServer::GetServiceName() const
{
	return TEXT("Notification");
}

FString UK2BeamNode_ApiRequest_PostServer::GetEndpointName() const
{
	return TEXT("PostServer");
}

UClass* UK2BeamNode_ApiRequest_PostServer::GetApiClass() const
{
	return UBeamNotificationApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostServer::GetRequestClass() const
{
	return UPostServerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostServer::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostServer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostServerSuccess");
}

FString UK2BeamNode_ApiRequest_PostServer::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostServerError");
}

FString UK2BeamNode_ApiRequest_PostServer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostServerComplete");
}

#undef LOCTEXT_NAMESPACE
