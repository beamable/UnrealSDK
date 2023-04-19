

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetPlans.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetPlansRequest.h"
#include "BeamableCore/Public/AutoGen/ServicePlansResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetPlans"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetPlans::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetPlans::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetPlans);
}

FName UK2BeamNode_ApiRequest_GetPlans::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetPlansRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetPlans::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetPlans::GetEndpointName() const
{
	return TEXT("GetPlans");
}

UClass* UK2BeamNode_ApiRequest_GetPlans::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPlans::GetRequestClass() const
{
	return UGetPlansRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPlans::GetResponseClass() const
{
	return UServicePlansResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetPlans::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetPlansSuccess");
}

FString UK2BeamNode_ApiRequest_GetPlans::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetPlansError");
}

FString UK2BeamNode_ApiRequest_GetPlans::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetPlansComplete");
}

#undef LOCTEXT_NAMESPACE
