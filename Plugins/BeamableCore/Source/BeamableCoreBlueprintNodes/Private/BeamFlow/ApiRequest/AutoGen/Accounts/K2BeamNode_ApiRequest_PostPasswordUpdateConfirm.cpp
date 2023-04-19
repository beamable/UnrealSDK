

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PostPasswordUpdateConfirm.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostPasswordUpdateConfirmRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostPasswordUpdateConfirm"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostPasswordUpdateConfirm::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostPasswordUpdateConfirm::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PostPasswordUpdateConfirm);
}

FName UK2BeamNode_ApiRequest_PostPasswordUpdateConfirm::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostPasswordUpdateConfirmRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostPasswordUpdateConfirm::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PostPasswordUpdateConfirm::GetEndpointName() const
{
	return TEXT("PostPasswordUpdateConfirm");
}

UClass* UK2BeamNode_ApiRequest_PostPasswordUpdateConfirm::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPasswordUpdateConfirm::GetRequestClass() const
{
	return UPostPasswordUpdateConfirmRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPasswordUpdateConfirm::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostPasswordUpdateConfirm::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostPasswordUpdateConfirmSuccess");
}

FString UK2BeamNode_ApiRequest_PostPasswordUpdateConfirm::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostPasswordUpdateConfirmError");
}

FString UK2BeamNode_ApiRequest_PostPasswordUpdateConfirm::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostPasswordUpdateConfirmComplete");
}

#undef LOCTEXT_NAMESPACE
