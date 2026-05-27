

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsStartResearch.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsStartResearchRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/StartResearchResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsStartResearch"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsStartResearch::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsStartResearch::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, StartResearch);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsStartResearch::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsStartResearchRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsStartResearch::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsStartResearch::GetEndpointName() const
{
	return TEXT("StartResearch");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsStartResearch::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsStartResearch::GetRequestClass() const
{
	return UBeamFarmMsStartResearchRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsStartResearch::GetResponseClass() const
{
	return UStartResearchResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsStartResearch::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsStartResearchSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsStartResearch::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsStartResearchError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsStartResearch::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsStartResearchComplete");
}

#undef LOCTEXT_NAMESPACE
