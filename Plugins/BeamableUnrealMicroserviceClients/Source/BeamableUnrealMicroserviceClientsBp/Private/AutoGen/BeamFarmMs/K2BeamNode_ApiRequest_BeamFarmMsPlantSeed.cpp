

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsPlantSeed.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsPlantSeedRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PlantResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsPlantSeed"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsPlantSeed::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsPlantSeed::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, PlantSeed);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsPlantSeed::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsPlantSeedRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsPlantSeed::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsPlantSeed::GetEndpointName() const
{
	return TEXT("PlantSeed");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsPlantSeed::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsPlantSeed::GetRequestClass() const
{
	return UBeamFarmMsPlantSeedRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsPlantSeed::GetResponseClass() const
{
	return UPlantResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsPlantSeed::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsPlantSeedSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsPlantSeed::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsPlantSeedError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsPlantSeed::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsPlantSeedComplete");
}

#undef LOCTEXT_NAMESPACE
