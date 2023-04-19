

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Notification/K2BeamNode_ApiRequest_PostPlayer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamNotificationApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Notification/PostPlayerRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostPlayer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostPlayer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostPlayer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, PostPlayer);
}

FName UK2BeamNode_ApiRequest_PostPlayer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostPlayerRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostPlayer::GetServiceName() const
{
	return TEXT("Notification");
}

FString UK2BeamNode_ApiRequest_PostPlayer::GetEndpointName() const
{
	return TEXT("PostPlayer");
}

UClass* UK2BeamNode_ApiRequest_PostPlayer::GetApiClass() const
{
	return UBeamNotificationApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPlayer::GetRequestClass() const
{
	return UPostPlayerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPlayer::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostPlayer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostPlayerSuccess");
}

FString UK2BeamNode_ApiRequest_PostPlayer::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostPlayerError");
}

FString UK2BeamNode_ApiRequest_PostPlayer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostPlayerComplete");
}

#undef LOCTEXT_NAMESPACE
