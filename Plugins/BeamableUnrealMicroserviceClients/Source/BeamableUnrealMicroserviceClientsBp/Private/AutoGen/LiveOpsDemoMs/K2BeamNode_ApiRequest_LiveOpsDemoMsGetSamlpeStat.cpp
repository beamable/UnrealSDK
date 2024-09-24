

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/LiveOpsDemoMs/K2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamLiveOpsDemoMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMs/LiveOpsDemoMsGetSamlpeStatRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsGetSamlpeStatResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMsApi, GetSamlpeStat);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(ULiveOpsDemoMsGetSamlpeStatRequest, Make);
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat::GetServiceName() const
{
	return TEXT("LiveOpsDemoMs");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat::GetEndpointName() const
{
	return TEXT("GetSamlpeStat");
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat::GetApiClass() const
{
	return UBeamLiveOpsDemoMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat::GetRequestClass() const
{
	return ULiveOpsDemoMsGetSamlpeStatRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat::GetResponseClass() const
{
	return ULiveOpsDemoMsGetSamlpeStatResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat::GetRequestSuccessDelegateName() const
{
	return TEXT("OnLiveOpsDemoMsGetSamlpeStatSuccess");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat::GetRequestErrorDelegateName() const
{
	return TEXT("OnLiveOpsDemoMsGetSamlpeStatError");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsGetSamlpeStat::GetRequestCompleteDelegateName() const
{
	return TEXT("OnLiveOpsDemoMsGetSamlpeStatComplete");
}

#undef LOCTEXT_NAMESPACE
