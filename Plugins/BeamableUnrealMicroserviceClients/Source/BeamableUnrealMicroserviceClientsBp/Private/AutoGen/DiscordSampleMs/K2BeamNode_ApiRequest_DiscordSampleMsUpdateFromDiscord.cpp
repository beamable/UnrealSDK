

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/DiscordSampleMs/K2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamDiscordSampleMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/DiscordSampleMs/DiscordSampleMsUpdateFromDiscordRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordSampleMsUpdateFromDiscordResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamDiscordSampleMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamDiscordSampleMsApi, UpdateFromDiscord);
}

FName UK2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDiscordSampleMsUpdateFromDiscordRequest, Make);
}

FString UK2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord::GetServiceName() const
{
	return TEXT("DiscordSampleMs");
}

FString UK2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord::GetEndpointName() const
{
	return TEXT("UpdateFromDiscord");
}

UClass* UK2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord::GetApiClass() const
{
	return UBeamDiscordSampleMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord::GetRequestClass() const
{
	return UDiscordSampleMsUpdateFromDiscordRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord::GetResponseClass() const
{
	return UDiscordSampleMsUpdateFromDiscordResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDiscordSampleMsUpdateFromDiscordSuccess");
}

FString UK2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord::GetRequestErrorDelegateName() const
{
	return TEXT("OnDiscordSampleMsUpdateFromDiscordError");
}

FString UK2BeamNode_ApiRequest_DiscordSampleMsUpdateFromDiscord::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDiscordSampleMsUpdateFromDiscordComplete");
}

#undef LOCTEXT_NAMESPACE
