

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsCollectResearch.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsCollectResearchRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectResearchResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsCollectResearch"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsCollectResearch::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsCollectResearch::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, CollectResearch);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsCollectResearch::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsCollectResearchRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectResearch::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectResearch::GetEndpointName() const
{
	return TEXT("CollectResearch");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsCollectResearch::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsCollectResearch::GetRequestClass() const
{
	return UBeamFarmMsCollectResearchRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsCollectResearch::GetResponseClass() const
{
	return UCollectResearchResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectResearch::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsCollectResearchSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectResearch::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsCollectResearchError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectResearch::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsCollectResearchComplete");
}

#undef LOCTEXT_NAMESPACE
