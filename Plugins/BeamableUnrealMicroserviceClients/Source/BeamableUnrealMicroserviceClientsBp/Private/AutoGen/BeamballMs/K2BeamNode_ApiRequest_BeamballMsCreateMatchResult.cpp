

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamballMs/K2BeamNode_ApiRequest_BeamballMsCreateMatchResult.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamballMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamballMs/BeamballMsCreateMatchResultRequest.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamballMsCreateMatchResult"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamballMsCreateMatchResult::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamballMsCreateMatchResult::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, CreateMatchResult);
}

FName UK2BeamNode_ApiRequest_BeamballMsCreateMatchResult::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamballMsCreateMatchResultRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamballMsCreateMatchResult::GetServiceName() const
{
	return TEXT("BeamballMs");
}

FString UK2BeamNode_ApiRequest_BeamballMsCreateMatchResult::GetEndpointName() const
{
	return TEXT("CreateMatchResult");
}

UClass* UK2BeamNode_ApiRequest_BeamballMsCreateMatchResult::GetApiClass() const
{
	return UBeamBeamballMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamballMsCreateMatchResult::GetRequestClass() const
{
	return UBeamballMsCreateMatchResultRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamballMsCreateMatchResult::GetResponseClass() const
{
	return UBeamPlainTextResponseBody::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamballMsCreateMatchResult::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamballMsCreateMatchResultSuccess");
}

FString UK2BeamNode_ApiRequest_BeamballMsCreateMatchResult::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamballMsCreateMatchResultError");
}

FString UK2BeamNode_ApiRequest_BeamballMsCreateMatchResult::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamballMsCreateMatchResultComplete");
}

#undef LOCTEXT_NAMESPACE
