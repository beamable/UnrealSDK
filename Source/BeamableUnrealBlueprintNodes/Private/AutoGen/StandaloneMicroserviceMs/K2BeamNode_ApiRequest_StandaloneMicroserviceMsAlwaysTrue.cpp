

#include "BeamableUnrealBlueprintNodes/Public/AutoGen/StandaloneMicroserviceMs/K2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue.h"

#include "BeamK2.h"

#include "BeamableUnreal/AutoGen/SubSystems/BeamStandaloneMicroserviceMsApi.h"
#include "BeamableUnreal/AutoGen/SubSystems/StandaloneMicroserviceMs/StandaloneMicroserviceMsAlwaysTrueRequest.h"
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsAlwaysTrueResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStandaloneMicroserviceMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStandaloneMicroserviceMsApi, AlwaysTrue);
}

FName UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UStandaloneMicroserviceMsAlwaysTrueRequest, Make);
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue::GetServiceName() const
{
	return TEXT("StandaloneMicroserviceMs");
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue::GetEndpointName() const
{
	return TEXT("AlwaysTrue");
}

UClass* UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue::GetApiClass() const
{
	return UBeamStandaloneMicroserviceMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue::GetRequestClass() const
{
	return UStandaloneMicroserviceMsAlwaysTrueRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue::GetResponseClass() const
{
	return UStandaloneMicroserviceMsAlwaysTrueResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue::GetRequestSuccessDelegateName() const
{
	return TEXT("OnStandaloneMicroserviceMsAlwaysTrueSuccess");
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue::GetRequestErrorDelegateName() const
{
	return TEXT("OnStandaloneMicroserviceMsAlwaysTrueError");
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAlwaysTrue::GetRequestCompleteDelegateName() const
{
	return TEXT("OnStandaloneMicroserviceMsAlwaysTrueComplete");
}

#undef LOCTEXT_NAMESPACE
