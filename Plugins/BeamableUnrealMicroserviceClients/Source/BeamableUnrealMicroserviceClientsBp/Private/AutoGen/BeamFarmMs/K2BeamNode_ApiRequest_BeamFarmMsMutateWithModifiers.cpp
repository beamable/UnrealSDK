

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsMutateWithModifiersRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutateWithModifiersResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, MutateWithModifiers);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsMutateWithModifiersRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers::GetEndpointName() const
{
	return TEXT("MutateWithModifiers");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers::GetRequestClass() const
{
	return UBeamFarmMsMutateWithModifiersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers::GetResponseClass() const
{
	return UMutateWithModifiersResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsMutateWithModifiersSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsMutateWithModifiersError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsMutateWithModifiers::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsMutateWithModifiersComplete");
}

#undef LOCTEXT_NAMESPACE
