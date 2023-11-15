

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Session/K2BeamNode_ApiRequest_BasicSessionGetStatus.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamSessionApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/BasicSessionGetStatusRequest.h"
#include "BeamableCore/Public/AutoGen/OnlineStatusResponses.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicSessionGetStatus"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicSessionGetStatus::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicSessionGetStatus::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, GetStatus);
}

FName UK2BeamNode_ApiRequest_BasicSessionGetStatus::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicSessionGetStatusRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicSessionGetStatus::GetServiceName() const
{
	return TEXT("Session");
}

FString UK2BeamNode_ApiRequest_BasicSessionGetStatus::GetEndpointName() const
{
	return TEXT("GetStatus");
}

UClass* UK2BeamNode_ApiRequest_BasicSessionGetStatus::GetApiClass() const
{
	return UBeamSessionApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicSessionGetStatus::GetRequestClass() const
{
	return UBasicSessionGetStatusRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicSessionGetStatus::GetResponseClass() const
{
	return UOnlineStatusResponses::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicSessionGetStatus::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicSessionGetStatusSuccess");
}

FString UK2BeamNode_ApiRequest_BasicSessionGetStatus::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicSessionGetStatusError");
}

FString UK2BeamNode_ApiRequest_BasicSessionGetStatus::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicSessionGetStatusComplete");
}

#undef LOCTEXT_NAMESPACE
