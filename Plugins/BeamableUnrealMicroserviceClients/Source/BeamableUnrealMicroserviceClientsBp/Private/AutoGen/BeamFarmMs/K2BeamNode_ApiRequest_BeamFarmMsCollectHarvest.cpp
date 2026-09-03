

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsCollectHarvest.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsCollectHarvestRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsCollectHarvest"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsCollectHarvest::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsCollectHarvest::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, CollectHarvest);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsCollectHarvest::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsCollectHarvestRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectHarvest::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectHarvest::GetEndpointName() const
{
	return TEXT("CollectHarvest");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsCollectHarvest::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsCollectHarvest::GetRequestClass() const
{
	return UBeamFarmMsCollectHarvestRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsCollectHarvest::GetResponseClass() const
{
	return UCollectResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectHarvest::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsCollectHarvestSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectHarvest::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsCollectHarvestError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectHarvest::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsCollectHarvestComplete");
}

#undef LOCTEXT_NAMESPACE
