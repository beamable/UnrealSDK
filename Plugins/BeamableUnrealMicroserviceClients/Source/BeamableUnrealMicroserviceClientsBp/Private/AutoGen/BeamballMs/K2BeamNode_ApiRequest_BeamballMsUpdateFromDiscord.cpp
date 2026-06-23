

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamballMs/K2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamballMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamballMs/BeamballMsUpdateFromDiscordRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballMsUpdateFromDiscordResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, UpdateFromDiscord);
}

FName UK2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamballMsUpdateFromDiscordRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord::GetServiceName() const
{
	return TEXT("BeamballMs");
}

FString UK2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord::GetEndpointName() const
{
	return TEXT("UpdateFromDiscord");
}

UClass* UK2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord::GetApiClass() const
{
	return UBeamBeamballMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord::GetRequestClass() const
{
	return UBeamballMsUpdateFromDiscordRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord::GetResponseClass() const
{
	return UBeamballMsUpdateFromDiscordResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamballMsUpdateFromDiscordSuccess");
}

FString UK2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamballMsUpdateFromDiscordError");
}

FString UK2BeamNode_ApiRequest_BeamballMsUpdateFromDiscord::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamballMsUpdateFromDiscordComplete");
}

#undef LOCTEXT_NAMESPACE
