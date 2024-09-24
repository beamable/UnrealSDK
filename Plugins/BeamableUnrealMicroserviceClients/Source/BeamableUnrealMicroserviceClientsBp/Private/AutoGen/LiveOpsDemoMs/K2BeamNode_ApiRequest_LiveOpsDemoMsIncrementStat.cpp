

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/LiveOpsDemoMs/K2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamLiveOpsDemoMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMs/LiveOpsDemoMsIncrementStatRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsIncrementStatResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMsApi, IncrementStat);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(ULiveOpsDemoMsIncrementStatRequest, Make);
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat::GetServiceName() const
{
	return TEXT("LiveOpsDemoMs");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat::GetEndpointName() const
{
	return TEXT("IncrementStat");
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat::GetApiClass() const
{
	return UBeamLiveOpsDemoMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat::GetRequestClass() const
{
	return ULiveOpsDemoMsIncrementStatRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat::GetResponseClass() const
{
	return ULiveOpsDemoMsIncrementStatResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat::GetRequestSuccessDelegateName() const
{
	return TEXT("OnLiveOpsDemoMsIncrementStatSuccess");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat::GetRequestErrorDelegateName() const
{
	return TEXT("OnLiveOpsDemoMsIncrementStatError");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsIncrementStat::GetRequestCompleteDelegateName() const
{
	return TEXT("OnLiveOpsDemoMsIncrementStatComplete");
}

#undef LOCTEXT_NAMESPACE
