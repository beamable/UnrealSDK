

#include "BeamableUnrealBlueprintNodes/Public/AutoGen/StandaloneMicroserviceMs/K2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString.h"

#include "BeamK2.h"

#include "BeamableUnreal/AutoGen/SubSystems/BeamStandaloneMicroserviceMsApi.h"
#include "BeamableUnreal/AutoGen/SubSystems/StandaloneMicroserviceMs/StandaloneMicroserviceMsJoinNumbersAsStringRequest.h"
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsJoinNumbersAsStringResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStandaloneMicroserviceMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStandaloneMicroserviceMsApi, JoinNumbersAsString);
}

FName UK2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UStandaloneMicroserviceMsJoinNumbersAsStringRequest, Make);
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString::GetServiceName() const
{
	return TEXT("StandaloneMicroserviceMs");
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString::GetEndpointName() const
{
	return TEXT("JoinNumbersAsString");
}

UClass* UK2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString::GetApiClass() const
{
	return UBeamStandaloneMicroserviceMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString::GetRequestClass() const
{
	return UStandaloneMicroserviceMsJoinNumbersAsStringRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString::GetResponseClass() const
{
	return UStandaloneMicroserviceMsJoinNumbersAsStringResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString::GetRequestSuccessDelegateName() const
{
	return TEXT("OnStandaloneMicroserviceMsJoinNumbersAsStringSuccess");
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString::GetRequestErrorDelegateName() const
{
	return TEXT("OnStandaloneMicroserviceMsJoinNumbersAsStringError");
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsJoinNumbersAsString::GetRequestCompleteDelegateName() const
{
	return TEXT("OnStandaloneMicroserviceMsJoinNumbersAsStringComplete");
}

#undef LOCTEXT_NAMESPACE
