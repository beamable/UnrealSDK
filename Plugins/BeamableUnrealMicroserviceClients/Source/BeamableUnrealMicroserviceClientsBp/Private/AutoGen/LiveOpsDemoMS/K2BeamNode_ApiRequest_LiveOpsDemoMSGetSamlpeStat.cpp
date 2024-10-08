

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/LiveOpsDemoMS/K2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamLiveOpsDemoMSApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMS/LiveOpsDemoMSGetSamlpeStatRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSGetSamlpeStatResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMSApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMSApi, GetSamlpeStat);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(ULiveOpsDemoMSGetSamlpeStatRequest, Make);
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat::GetServiceName() const
{
	return TEXT("LiveOpsDemoMS");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat::GetEndpointName() const
{
	return TEXT("GetSamlpeStat");
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat::GetApiClass() const
{
	return UBeamLiveOpsDemoMSApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat::GetRequestClass() const
{
	return ULiveOpsDemoMSGetSamlpeStatRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat::GetResponseClass() const
{
	return ULiveOpsDemoMSGetSamlpeStatResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat::GetRequestSuccessDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSGetSamlpeStatSuccess");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat::GetRequestErrorDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSGetSamlpeStatError");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSGetSamlpeStat::GetRequestCompleteDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSGetSamlpeStatComplete");
}

#undef LOCTEXT_NAMESPACE
