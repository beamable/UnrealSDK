

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsMutate.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsMutateRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutationResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsMutate"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsMutate::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsMutate::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, Mutate);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsMutate::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsMutateRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsMutate::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsMutate::GetEndpointName() const
{
	return TEXT("Mutate");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsMutate::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsMutate::GetRequestClass() const
{
	return UBeamFarmMsMutateRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsMutate::GetResponseClass() const
{
	return UMutationResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsMutate::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsMutateSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsMutate::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsMutateError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsMutate::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsMutateComplete");
}

#undef LOCTEXT_NAMESPACE
