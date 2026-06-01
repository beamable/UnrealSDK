

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsGetSlotStates.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsGetSlotStatesRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSlotStatesResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsGetSlotStates"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsGetSlotStates::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsGetSlotStates::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSlotStates);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsGetSlotStates::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsGetSlotStatesRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetSlotStates::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetSlotStates::GetEndpointName() const
{
	return TEXT("GetSlotStates");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsGetSlotStates::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsGetSlotStates::GetRequestClass() const
{
	return UBeamFarmMsGetSlotStatesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsGetSlotStates::GetResponseClass() const
{
	return UGetSlotStatesResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetSlotStates::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsGetSlotStatesSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetSlotStates::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsGetSlotStatesError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetSlotStates::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsGetSlotStatesComplete");
}

#undef LOCTEXT_NAMESPACE
