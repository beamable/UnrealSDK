

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Events/K2BeamNode_ApiRequest_GetRunning.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/GetRunningRequest.h"
#include "BeamableCore/Public/AutoGen/EventQueryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRunning"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRunning::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRunning::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetRunning);
}

FName UK2BeamNode_ApiRequest_GetRunning::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRunningRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRunning::GetServiceName() const
{
	return TEXT("Events");
}

FString UK2BeamNode_ApiRequest_GetRunning::GetEndpointName() const
{
	return TEXT("GetRunning");
}

UClass* UK2BeamNode_ApiRequest_GetRunning::GetApiClass() const
{
	return UBeamEventsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRunning::GetRequestClass() const
{
	return UGetRunningRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRunning::GetResponseClass() const
{
	return UEventQueryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRunning::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRunningSuccess");
}

FString UK2BeamNode_ApiRequest_GetRunning::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRunningError");
}

FString UK2BeamNode_ApiRequest_GetRunning::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRunningComplete");
}

#undef LOCTEXT_NAMESPACE
