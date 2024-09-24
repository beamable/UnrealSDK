

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/LiveOpsDemoMs/K2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamLiveOpsDemoMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMs/LiveOpsDemoMsPrepareNewPlayerRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsPrepareNewPlayerResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMsApi, PrepareNewPlayer);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(ULiveOpsDemoMsPrepareNewPlayerRequest, Make);
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer::GetServiceName() const
{
	return TEXT("LiveOpsDemoMs");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer::GetEndpointName() const
{
	return TEXT("PrepareNewPlayer");
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer::GetApiClass() const
{
	return UBeamLiveOpsDemoMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer::GetRequestClass() const
{
	return ULiveOpsDemoMsPrepareNewPlayerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer::GetResponseClass() const
{
	return ULiveOpsDemoMsPrepareNewPlayerResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnLiveOpsDemoMsPrepareNewPlayerSuccess");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer::GetRequestErrorDelegateName() const
{
	return TEXT("OnLiveOpsDemoMsPrepareNewPlayerError");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsPrepareNewPlayer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnLiveOpsDemoMsPrepareNewPlayerComplete");
}

#undef LOCTEXT_NAMESPACE
