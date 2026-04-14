

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/ServicePlan/K2BeamNode_ApiRequest_GetServicePlans.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamServicePlanApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/ServicePlan/GetServicePlansRequest.h"
#include "BeamableCore/Public/AutoGen/ServicePlanActorServicePlansResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetServicePlans"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetServicePlans::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamServicePlanApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetServicePlans::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamServicePlanApi, GetServicePlans);
}

FName UK2BeamNode_ApiRequest_GetServicePlans::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetServicePlansRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetServicePlans::GetServiceName() const
{
	return TEXT("ServicePlan");
}

FString UK2BeamNode_ApiRequest_GetServicePlans::GetEndpointName() const
{
	return TEXT("GetServicePlans");
}

UClass* UK2BeamNode_ApiRequest_GetServicePlans::GetApiClass() const
{
	return UBeamServicePlanApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetServicePlans::GetRequestClass() const
{
	return UGetServicePlansRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetServicePlans::GetResponseClass() const
{
	return UServicePlanActorServicePlansResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetServicePlans::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetServicePlansSuccess");
}

FString UK2BeamNode_ApiRequest_GetServicePlans::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetServicePlansError");
}

FString UK2BeamNode_ApiRequest_GetServicePlans::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetServicePlansComplete");
}

#undef LOCTEXT_NAMESPACE
