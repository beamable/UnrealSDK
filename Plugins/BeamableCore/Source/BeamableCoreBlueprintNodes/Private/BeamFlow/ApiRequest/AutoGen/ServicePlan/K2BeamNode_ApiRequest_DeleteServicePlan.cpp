

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/ServicePlan/K2BeamNode_ApiRequest_DeleteServicePlan.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamServicePlanApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/ServicePlan/DeleteServicePlanRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteServicePlan"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteServicePlan::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamServicePlanApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteServicePlan::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamServicePlanApi, DeleteServicePlan);
}

FName UK2BeamNode_ApiRequest_DeleteServicePlan::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteServicePlanRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteServicePlan::GetServiceName() const
{
	return TEXT("ServicePlan");
}

FString UK2BeamNode_ApiRequest_DeleteServicePlan::GetEndpointName() const
{
	return TEXT("DeleteServicePlan");
}

UClass* UK2BeamNode_ApiRequest_DeleteServicePlan::GetApiClass() const
{
	return UBeamServicePlanApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteServicePlan::GetRequestClass() const
{
	return UDeleteServicePlanRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteServicePlan::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteServicePlan::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteServicePlanSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteServicePlan::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteServicePlanError");
}

FString UK2BeamNode_ApiRequest_DeleteServicePlan::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteServicePlanComplete");
}

#undef LOCTEXT_NAMESPACE
