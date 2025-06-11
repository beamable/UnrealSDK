

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/LiveOpsDemoMS/K2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamLiveOpsDemoMSApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMS/LiveOpsDemoMSGetSampleStatRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSGetSampleStatResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMSApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMSApi, GetSampleStat);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(ULiveOpsDemoMSGetSampleStatRequest, Make);
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat::GetServiceName() const
{
	return TEXT("LiveOpsDemoMS");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat::GetEndpointName() const
{
	return TEXT("GetSampleStat");
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat::GetApiClass() const
{
	return UBeamLiveOpsDemoMSApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat::GetRequestClass() const
{
	return ULiveOpsDemoMSGetSampleStatRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat::GetResponseClass() const
{
	return ULiveOpsDemoMSGetSampleStatResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat::GetRequestSuccessDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSGetSampleStatSuccess");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat::GetRequestErrorDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSGetSampleStatError");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSampleStat::GetRequestCompleteDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSGetSampleStatComplete");
}

#undef LOCTEXT_NAMESPACE
