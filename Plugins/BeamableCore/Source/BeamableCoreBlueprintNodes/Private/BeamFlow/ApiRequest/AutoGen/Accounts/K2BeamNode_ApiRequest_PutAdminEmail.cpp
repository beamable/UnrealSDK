

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PutAdminEmail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PutAdminEmailRequest.h"
#include "BeamableCore/Public/AutoGen/AccountsObjectAccount.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutAdminEmail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutAdminEmail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutAdminEmail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PutAdminEmail);
}

FName UK2BeamNode_ApiRequest_PutAdminEmail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutAdminEmailRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutAdminEmail::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PutAdminEmail::GetEndpointName() const
{
	return TEXT("PutAdminEmail");
}

UClass* UK2BeamNode_ApiRequest_PutAdminEmail::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAdminEmail::GetRequestClass() const
{
	return UPutAdminEmailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAdminEmail::GetResponseClass() const
{
	return UAccountsObjectAccount::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutAdminEmail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutAdminEmailSuccess");
}

FString UK2BeamNode_ApiRequest_PutAdminEmail::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutAdminEmailError");
}

FString UK2BeamNode_ApiRequest_PutAdminEmail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutAdminEmailComplete");
}

#undef LOCTEXT_NAMESPACE
