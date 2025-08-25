

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamballMs/K2BeamNode_ApiRequest_BeamballMsProcessMatchResult.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamballMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamballMs/BeamballMsProcessMatchResultRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballMsProcessMatchResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamballMsProcessMatchResult"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamballMsProcessMatchResult::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamballMsProcessMatchResult::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, ProcessMatchResult);
}

FName UK2BeamNode_ApiRequest_BeamballMsProcessMatchResult::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamballMsProcessMatchResultRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamballMsProcessMatchResult::GetServiceName() const
{
	return TEXT("BeamballMs");
}

FString UK2BeamNode_ApiRequest_BeamballMsProcessMatchResult::GetEndpointName() const
{
	return TEXT("ProcessMatchResult");
}

UClass* UK2BeamNode_ApiRequest_BeamballMsProcessMatchResult::GetApiClass() const
{
	return UBeamBeamballMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamballMsProcessMatchResult::GetRequestClass() const
{
	return UBeamballMsProcessMatchResultRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamballMsProcessMatchResult::GetResponseClass() const
{
	return UBeamballMsProcessMatchResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamballMsProcessMatchResult::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamballMsProcessMatchResultSuccess");
}

FString UK2BeamNode_ApiRequest_BeamballMsProcessMatchResult::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamballMsProcessMatchResultError");
}

FString UK2BeamNode_ApiRequest_BeamballMsProcessMatchResult::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamballMsProcessMatchResultComplete");
}

#undef LOCTEXT_NAMESPACE
