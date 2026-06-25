

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsSendPushToPlayerRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/AdminSendResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, SendPushToPlayer);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsSendPushToPlayerRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer::GetEndpointName() const
{
	return TEXT("SendPushToPlayer");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer::GetRequestClass() const
{
	return UBeamFarmMsSendPushToPlayerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer::GetResponseClass() const
{
	return UAdminSendResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsSendPushToPlayerSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsSendPushToPlayerError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendPushToPlayer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsSendPushToPlayerComplete");
}

#undef LOCTEXT_NAMESPACE
