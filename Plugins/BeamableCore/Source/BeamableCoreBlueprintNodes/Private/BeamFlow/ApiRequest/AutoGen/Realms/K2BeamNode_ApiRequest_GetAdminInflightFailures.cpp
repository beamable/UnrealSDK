

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetAdminInflightFailures.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetAdminInflightFailuresRequest.h"
#include "BeamableCore/Public/AutoGen/InFlightFailureResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAdminInflightFailures"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAdminInflightFailures::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAdminInflightFailures::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetAdminInflightFailures);
}

FName UK2BeamNode_ApiRequest_GetAdminInflightFailures::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAdminInflightFailuresRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAdminInflightFailures::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetAdminInflightFailures::GetEndpointName() const
{
	return TEXT("GetAdminInflightFailures");
}

UClass* UK2BeamNode_ApiRequest_GetAdminInflightFailures::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAdminInflightFailures::GetRequestClass() const
{
	return UGetAdminInflightFailuresRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAdminInflightFailures::GetResponseClass() const
{
	return UInFlightFailureResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAdminInflightFailures::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAdminInflightFailuresSuccess");
}

FString UK2BeamNode_ApiRequest_GetAdminInflightFailures::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAdminInflightFailuresError");
}

FString UK2BeamNode_ApiRequest_GetAdminInflightFailures::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAdminInflightFailuresComplete");
}

#undef LOCTEXT_NAMESPACE
