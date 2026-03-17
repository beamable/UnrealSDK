

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Session/K2BeamNode_ApiRequest_ApiSessionPostHeartbeat.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamSessionApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/ApiSessionPostHeartbeatRequest.h"
#include "BeamableCore/Public/AutoGen/ApiSessionsHeartbeatPostSessionResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiSessionPostHeartbeat"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiSessionPostHeartbeat::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiSessionPostHeartbeat::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, ApiSessionPostHeartbeat);
}

FName UK2BeamNode_ApiRequest_ApiSessionPostHeartbeat::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiSessionPostHeartbeatRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiSessionPostHeartbeat::GetServiceName() const
{
	return TEXT("Session");
}

FString UK2BeamNode_ApiRequest_ApiSessionPostHeartbeat::GetEndpointName() const
{
	return TEXT("ApiSessionPostHeartbeat");
}

UClass* UK2BeamNode_ApiRequest_ApiSessionPostHeartbeat::GetApiClass() const
{
	return UBeamSessionApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiSessionPostHeartbeat::GetRequestClass() const
{
	return UApiSessionPostHeartbeatRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiSessionPostHeartbeat::GetResponseClass() const
{
	return UApiSessionsHeartbeatPostSessionResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiSessionPostHeartbeat::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiSessionPostHeartbeatSuccess");
}

FString UK2BeamNode_ApiRequest_ApiSessionPostHeartbeat::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiSessionPostHeartbeatError");
}

FString UK2BeamNode_ApiRequest_ApiSessionPostHeartbeat::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiSessionPostHeartbeatComplete");
}

#undef LOCTEXT_NAMESPACE
