

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/DiscordSampleMs/K2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamDiscordSampleMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/DiscordSampleMs/DiscordSampleMsUpdateUserWhitelistedStatusRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordWhitelistedInfo.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamDiscordSampleMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamDiscordSampleMsApi, UpdateUserWhitelistedStatus);
}

FName UK2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDiscordSampleMsUpdateUserWhitelistedStatusRequest, Make);
}

FString UK2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus::GetServiceName() const
{
	return TEXT("DiscordSampleMs");
}

FString UK2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus::GetEndpointName() const
{
	return TEXT("UpdateUserWhitelistedStatus");
}

UClass* UK2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus::GetApiClass() const
{
	return UBeamDiscordSampleMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus::GetRequestClass() const
{
	return UDiscordSampleMsUpdateUserWhitelistedStatusRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus::GetResponseClass() const
{
	return UDiscordWhitelistedInfo::StaticClass();
}

FString UK2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDiscordSampleMsUpdateUserWhitelistedStatusSuccess");
}

FString UK2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus::GetRequestErrorDelegateName() const
{
	return TEXT("OnDiscordSampleMsUpdateUserWhitelistedStatusError");
}

FString UK2BeamNode_ApiRequest_DiscordSampleMsUpdateUserWhitelistedStatus::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDiscordSampleMsUpdateUserWhitelistedStatusComplete");
}

#undef LOCTEXT_NAMESPACE
