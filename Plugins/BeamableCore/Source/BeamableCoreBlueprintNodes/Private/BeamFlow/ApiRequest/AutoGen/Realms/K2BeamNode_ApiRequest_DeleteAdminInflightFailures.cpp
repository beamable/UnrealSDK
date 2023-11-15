

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_DeleteAdminInflightFailures.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/DeleteAdminInflightFailuresRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteAdminInflightFailures"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteAdminInflightFailures::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteAdminInflightFailures::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, DeleteAdminInflightFailures);
}

FName UK2BeamNode_ApiRequest_DeleteAdminInflightFailures::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteAdminInflightFailuresRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteAdminInflightFailures::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_DeleteAdminInflightFailures::GetEndpointName() const
{
	return TEXT("DeleteAdminInflightFailures");
}

UClass* UK2BeamNode_ApiRequest_DeleteAdminInflightFailures::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteAdminInflightFailures::GetRequestClass() const
{
	return UDeleteAdminInflightFailuresRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteAdminInflightFailures::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteAdminInflightFailures::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteAdminInflightFailuresSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteAdminInflightFailures::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteAdminInflightFailuresError");
}

FString UK2BeamNode_ApiRequest_DeleteAdminInflightFailures::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteAdminInflightFailuresComplete");
}

#undef LOCTEXT_NAMESPACE
