

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Notification/K2BeamNode_ApiRequest_BasicNotificationPostGame.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamNotificationApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Notification/BasicNotificationPostGameRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicNotificationPostGame"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicNotificationPostGame::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicNotificationPostGame::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, PostGame);
}

FName UK2BeamNode_ApiRequest_BasicNotificationPostGame::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicNotificationPostGameRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicNotificationPostGame::GetServiceName() const
{
	return TEXT("Notification");
}

FString UK2BeamNode_ApiRequest_BasicNotificationPostGame::GetEndpointName() const
{
	return TEXT("PostGame");
}

UClass* UK2BeamNode_ApiRequest_BasicNotificationPostGame::GetApiClass() const
{
	return UBeamNotificationApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicNotificationPostGame::GetRequestClass() const
{
	return UBasicNotificationPostGameRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicNotificationPostGame::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicNotificationPostGame::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicNotificationPostGameSuccess");
}

FString UK2BeamNode_ApiRequest_BasicNotificationPostGame::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicNotificationPostGameError");
}

FString UK2BeamNode_ApiRequest_BasicNotificationPostGame::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicNotificationPostGameComplete");
}

#undef LOCTEXT_NAMESPACE
