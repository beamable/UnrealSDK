

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/ServicePlan/K2BeamNode_ApiRequest_GetServicePlan.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamServicePlanApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/ServicePlan/GetServicePlanRequest.h"
#include "BeamableCore/Public/AutoGen/ServicePlanActorServicePlan.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetServicePlan"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetServicePlan::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamServicePlanApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetServicePlan::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamServicePlanApi, GetServicePlan);
}

FName UK2BeamNode_ApiRequest_GetServicePlan::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetServicePlanRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetServicePlan::GetServiceName() const
{
	return TEXT("ServicePlan");
}

FString UK2BeamNode_ApiRequest_GetServicePlan::GetEndpointName() const
{
	return TEXT("GetServicePlan");
}

UClass* UK2BeamNode_ApiRequest_GetServicePlan::GetApiClass() const
{
	return UBeamServicePlanApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetServicePlan::GetRequestClass() const
{
	return UGetServicePlanRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetServicePlan::GetResponseClass() const
{
	return UServicePlanActorServicePlan::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetServicePlan::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetServicePlanSuccess");
}

FString UK2BeamNode_ApiRequest_GetServicePlan::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetServicePlanError");
}

FString UK2BeamNode_ApiRequest_GetServicePlan::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetServicePlanComplete");
}

#undef LOCTEXT_NAMESPACE
