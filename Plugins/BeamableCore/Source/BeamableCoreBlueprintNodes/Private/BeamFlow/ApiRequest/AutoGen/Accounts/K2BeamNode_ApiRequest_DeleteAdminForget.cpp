

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_DeleteAdminForget.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/DeleteAdminForgetRequest.h"
#include "BeamableCore/Public/AutoGen/AccountsObjectAccount.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteAdminForget"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteAdminForget::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteAdminForget::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, DeleteAdminForget);
}

FName UK2BeamNode_ApiRequest_DeleteAdminForget::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteAdminForgetRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteAdminForget::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_DeleteAdminForget::GetEndpointName() const
{
	return TEXT("DeleteAdminForget");
}

UClass* UK2BeamNode_ApiRequest_DeleteAdminForget::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteAdminForget::GetRequestClass() const
{
	return UDeleteAdminForgetRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteAdminForget::GetResponseClass() const
{
	return UAccountsObjectAccount::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteAdminForget::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteAdminForgetSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteAdminForget::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteAdminForgetError");
}

FString UK2BeamNode_ApiRequest_DeleteAdminForget::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteAdminForgetComplete");
}

#undef LOCTEXT_NAMESPACE
