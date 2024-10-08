

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/LiveOpsDemoMS/K2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamLiveOpsDemoMSApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMS/LiveOpsDemoMSIncrementStatRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSIncrementStatResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMSApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMSApi, IncrementStat);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(ULiveOpsDemoMSIncrementStatRequest, Make);
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat::GetServiceName() const
{
	return TEXT("LiveOpsDemoMS");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat::GetEndpointName() const
{
	return TEXT("IncrementStat");
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat::GetApiClass() const
{
	return UBeamLiveOpsDemoMSApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat::GetRequestClass() const
{
	return ULiveOpsDemoMSIncrementStatRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat::GetResponseClass() const
{
	return ULiveOpsDemoMSIncrementStatResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat::GetRequestSuccessDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSIncrementStatSuccess");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat::GetRequestErrorDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSIncrementStatError");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSIncrementStat::GetRequestCompleteDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSIncrementStatComplete");
}

#undef LOCTEXT_NAMESPACE
