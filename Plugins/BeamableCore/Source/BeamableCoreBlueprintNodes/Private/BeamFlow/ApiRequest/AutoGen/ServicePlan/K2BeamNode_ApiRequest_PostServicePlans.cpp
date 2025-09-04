

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/ServicePlan/K2BeamNode_ApiRequest_PostServicePlans.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamServicePlanApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/ServicePlan/PostServicePlansRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostServicePlans"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostServicePlans::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamServicePlanApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostServicePlans::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamServicePlanApi, PostServicePlans);
}

FName UK2BeamNode_ApiRequest_PostServicePlans::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostServicePlansRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostServicePlans::GetServiceName() const
{
	return TEXT("ServicePlan");
}

FString UK2BeamNode_ApiRequest_PostServicePlans::GetEndpointName() const
{
	return TEXT("PostServicePlans");
}

UClass* UK2BeamNode_ApiRequest_PostServicePlans::GetApiClass() const
{
	return UBeamServicePlanApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostServicePlans::GetRequestClass() const
{
	return UPostServicePlansRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostServicePlans::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostServicePlans::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostServicePlansSuccess");
}

FString UK2BeamNode_ApiRequest_PostServicePlans::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostServicePlansError");
}

FString UK2BeamNode_ApiRequest_PostServicePlans::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostServicePlansComplete");
}

#undef LOCTEXT_NAMESPACE
