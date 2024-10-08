

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/LiveOpsDemoMS/K2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamLiveOpsDemoMSApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMS/LiveOpsDemoMSPrepareNewPlayerRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSPrepareNewPlayerResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMSApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMSApi, PrepareNewPlayer);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(ULiveOpsDemoMSPrepareNewPlayerRequest, Make);
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer::GetServiceName() const
{
	return TEXT("LiveOpsDemoMS");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer::GetEndpointName() const
{
	return TEXT("PrepareNewPlayer");
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer::GetApiClass() const
{
	return UBeamLiveOpsDemoMSApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer::GetRequestClass() const
{
	return ULiveOpsDemoMSPrepareNewPlayerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer::GetResponseClass() const
{
	return ULiveOpsDemoMSPrepareNewPlayerResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSPrepareNewPlayerSuccess");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer::GetRequestErrorDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSPrepareNewPlayerError");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSPrepareNewPlayer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSPrepareNewPlayerComplete");
}

#undef LOCTEXT_NAMESPACE
