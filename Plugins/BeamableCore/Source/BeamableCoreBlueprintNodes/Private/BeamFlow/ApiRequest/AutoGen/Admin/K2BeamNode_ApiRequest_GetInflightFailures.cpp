

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Admin/K2BeamNode_ApiRequest_GetInflightFailures.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAdminApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Admin/GetInflightFailuresRequest.h"
#include "BeamableCore/Public/AutoGen/InFlightFailureResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetInflightFailures"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetInflightFailures::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAdminApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetInflightFailures::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAdminApi, GetInflightFailures);
}

FName UK2BeamNode_ApiRequest_GetInflightFailures::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetInflightFailuresRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetInflightFailures::GetServiceName() const
{
	return TEXT("Admin");
}

FString UK2BeamNode_ApiRequest_GetInflightFailures::GetEndpointName() const
{
	return TEXT("GetInflightFailures");
}

UClass* UK2BeamNode_ApiRequest_GetInflightFailures::GetApiClass() const
{
	return UBeamAdminApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetInflightFailures::GetRequestClass() const
{
	return UGetInflightFailuresRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetInflightFailures::GetResponseClass() const
{
	return UInFlightFailureResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetInflightFailures::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetInflightFailuresSuccess");
}

FString UK2BeamNode_ApiRequest_GetInflightFailures::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetInflightFailuresError");
}

FString UK2BeamNode_ApiRequest_GetInflightFailures::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetInflightFailuresComplete");
}

#undef LOCTEXT_NAMESPACE
