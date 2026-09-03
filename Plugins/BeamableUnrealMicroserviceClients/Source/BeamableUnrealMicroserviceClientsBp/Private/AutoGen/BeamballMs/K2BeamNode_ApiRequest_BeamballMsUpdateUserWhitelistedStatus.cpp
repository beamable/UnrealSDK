

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamballMs/K2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamballMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamballMs/BeamballMsUpdateUserWhitelistedStatusRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordWhitelistedInfo.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, UpdateUserWhitelistedStatus);
}

FName UK2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamballMsUpdateUserWhitelistedStatusRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus::GetServiceName() const
{
	return TEXT("BeamballMs");
}

FString UK2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus::GetEndpointName() const
{
	return TEXT("UpdateUserWhitelistedStatus");
}

UClass* UK2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus::GetApiClass() const
{
	return UBeamBeamballMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus::GetRequestClass() const
{
	return UBeamballMsUpdateUserWhitelistedStatusRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus::GetResponseClass() const
{
	return UDiscordWhitelistedInfo::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamballMsUpdateUserWhitelistedStatusSuccess");
}

FString UK2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamballMsUpdateUserWhitelistedStatusError");
}

FString UK2BeamNode_ApiRequest_BeamballMsUpdateUserWhitelistedStatus::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamballMsUpdateUserWhitelistedStatusComplete");
}

#undef LOCTEXT_NAMESPACE
