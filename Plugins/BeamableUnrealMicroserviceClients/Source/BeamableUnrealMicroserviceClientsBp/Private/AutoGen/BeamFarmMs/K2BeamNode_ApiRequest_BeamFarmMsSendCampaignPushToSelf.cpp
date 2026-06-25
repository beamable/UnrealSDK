

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsSendCampaignPushToSelfRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, SendCampaignPushToSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsSendCampaignPushToSelfRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf::GetEndpointName() const
{
	return TEXT("SendCampaignPushToSelf");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf::GetRequestClass() const
{
	return UBeamFarmMsSendCampaignPushToSelfRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf::GetResponseClass() const
{
	return USendResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsSendCampaignPushToSelfSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsSendCampaignPushToSelfError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendCampaignPushToSelf::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsSendCampaignPushToSelfComplete");
}

#undef LOCTEXT_NAMESPACE
