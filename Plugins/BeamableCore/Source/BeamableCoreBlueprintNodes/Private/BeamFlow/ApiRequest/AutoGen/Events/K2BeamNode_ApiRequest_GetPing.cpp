

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Events/K2BeamNode_ApiRequest_GetPing.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/GetPingRequest.h"
#include "BeamableCore/Public/AutoGen/PingRsp.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetPing"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetPing::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetPing::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetPing);
}

FName UK2BeamNode_ApiRequest_GetPing::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetPingRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetPing::GetServiceName() const
{
	return TEXT("Events");
}

FString UK2BeamNode_ApiRequest_GetPing::GetEndpointName() const
{
	return TEXT("GetPing");
}

UClass* UK2BeamNode_ApiRequest_GetPing::GetApiClass() const
{
	return UBeamEventsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPing::GetRequestClass() const
{
	return UGetPingRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPing::GetResponseClass() const
{
	return UPingRsp::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetPing::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetPingSuccess");
}

FString UK2BeamNode_ApiRequest_GetPing::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetPingError");
}

FString UK2BeamNode_ApiRequest_GetPing::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetPingComplete");
}

#undef LOCTEXT_NAMESPACE
