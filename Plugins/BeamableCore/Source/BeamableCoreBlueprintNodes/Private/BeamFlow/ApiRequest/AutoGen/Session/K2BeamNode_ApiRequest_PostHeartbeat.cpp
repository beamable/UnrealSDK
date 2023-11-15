

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Session/K2BeamNode_ApiRequest_PostHeartbeat.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamSessionApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/PostHeartbeatRequest.h"
#include "BeamableCore/Public/AutoGen/SessionHeartbeat.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostHeartbeat"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostHeartbeat::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostHeartbeat::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, PostHeartbeat);
}

FName UK2BeamNode_ApiRequest_PostHeartbeat::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostHeartbeatRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostHeartbeat::GetServiceName() const
{
	return TEXT("Session");
}

FString UK2BeamNode_ApiRequest_PostHeartbeat::GetEndpointName() const
{
	return TEXT("PostHeartbeat");
}

UClass* UK2BeamNode_ApiRequest_PostHeartbeat::GetApiClass() const
{
	return UBeamSessionApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostHeartbeat::GetRequestClass() const
{
	return UPostHeartbeatRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostHeartbeat::GetResponseClass() const
{
	return USessionHeartbeat::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostHeartbeat::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostHeartbeatSuccess");
}

FString UK2BeamNode_ApiRequest_PostHeartbeat::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostHeartbeatError");
}

FString UK2BeamNode_ApiRequest_PostHeartbeat::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostHeartbeatComplete");
}

#undef LOCTEXT_NAMESPACE
