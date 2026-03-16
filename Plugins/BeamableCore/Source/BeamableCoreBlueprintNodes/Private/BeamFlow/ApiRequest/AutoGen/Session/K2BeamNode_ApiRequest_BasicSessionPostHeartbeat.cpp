

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Session/K2BeamNode_ApiRequest_BasicSessionPostHeartbeat.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamSessionApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/BasicSessionPostHeartbeatRequest.h"
#include "BeamableCore/Public/AutoGen/SessionHeartbeat.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicSessionPostHeartbeat"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicSessionPostHeartbeat::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicSessionPostHeartbeat::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, BasicSessionPostHeartbeat);
}

FName UK2BeamNode_ApiRequest_BasicSessionPostHeartbeat::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicSessionPostHeartbeatRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicSessionPostHeartbeat::GetServiceName() const
{
	return TEXT("Session");
}

FString UK2BeamNode_ApiRequest_BasicSessionPostHeartbeat::GetEndpointName() const
{
	return TEXT("BasicSessionPostHeartbeat");
}

UClass* UK2BeamNode_ApiRequest_BasicSessionPostHeartbeat::GetApiClass() const
{
	return UBeamSessionApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicSessionPostHeartbeat::GetRequestClass() const
{
	return UBasicSessionPostHeartbeatRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicSessionPostHeartbeat::GetResponseClass() const
{
	return USessionHeartbeat::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicSessionPostHeartbeat::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicSessionPostHeartbeatSuccess");
}

FString UK2BeamNode_ApiRequest_BasicSessionPostHeartbeat::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicSessionPostHeartbeatError");
}

FString UK2BeamNode_ApiRequest_BasicSessionPostHeartbeat::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicSessionPostHeartbeatComplete");
}

#undef LOCTEXT_NAMESPACE
