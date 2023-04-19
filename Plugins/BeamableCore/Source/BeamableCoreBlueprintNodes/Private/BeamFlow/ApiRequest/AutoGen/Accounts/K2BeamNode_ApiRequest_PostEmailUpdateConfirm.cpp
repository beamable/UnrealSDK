

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PostEmailUpdateConfirm.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostEmailUpdateConfirmRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostEmailUpdateConfirm"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostEmailUpdateConfirm::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostEmailUpdateConfirm::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PostEmailUpdateConfirm);
}

FName UK2BeamNode_ApiRequest_PostEmailUpdateConfirm::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostEmailUpdateConfirmRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostEmailUpdateConfirm::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PostEmailUpdateConfirm::GetEndpointName() const
{
	return TEXT("PostEmailUpdateConfirm");
}

UClass* UK2BeamNode_ApiRequest_PostEmailUpdateConfirm::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostEmailUpdateConfirm::GetRequestClass() const
{
	return UPostEmailUpdateConfirmRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostEmailUpdateConfirm::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostEmailUpdateConfirm::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostEmailUpdateConfirmSuccess");
}

FString UK2BeamNode_ApiRequest_PostEmailUpdateConfirm::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostEmailUpdateConfirmError");
}

FString UK2BeamNode_ApiRequest_PostEmailUpdateConfirm::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostEmailUpdateConfirmComplete");
}

#undef LOCTEXT_NAMESPACE
