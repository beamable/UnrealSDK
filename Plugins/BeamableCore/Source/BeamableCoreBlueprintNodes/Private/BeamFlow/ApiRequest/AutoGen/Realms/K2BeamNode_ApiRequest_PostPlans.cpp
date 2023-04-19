

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PostPlans.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostPlansRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostPlans"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostPlans::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostPlans::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PostPlans);
}

FName UK2BeamNode_ApiRequest_PostPlans::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostPlansRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostPlans::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PostPlans::GetEndpointName() const
{
	return TEXT("PostPlans");
}

UClass* UK2BeamNode_ApiRequest_PostPlans::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPlans::GetRequestClass() const
{
	return UPostPlansRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPlans::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostPlans::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostPlansSuccess");
}

FString UK2BeamNode_ApiRequest_PostPlans::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostPlansError");
}

FString UK2BeamNode_ApiRequest_PostPlans::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostPlansComplete");
}

#undef LOCTEXT_NAMESPACE
