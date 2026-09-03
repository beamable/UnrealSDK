

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsSendCampaignPushToPlayerRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/AdminSendResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, SendCampaignPushToPlayer);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsSendCampaignPushToPlayerRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer::GetEndpointName() const
{
	return TEXT("SendCampaignPushToPlayer");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer::GetRequestClass() const
{
	return UBeamFarmMsSendCampaignPushToPlayerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer::GetResponseClass() const
{
	return UAdminSendResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsSendCampaignPushToPlayerSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsSendCampaignPushToPlayerError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToPlayer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsSendCampaignPushToPlayerComplete");
}

#undef LOCTEXT_NAMESPACE
