

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PutAccounts.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PutAccountsRequest.h"
#include "BeamableCore/Public/AutoGen/AccountsObjectAccount.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutAccounts"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutAccounts::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutAccounts::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PutAccounts);
}

FName UK2BeamNode_ApiRequest_PutAccounts::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutAccountsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutAccounts::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PutAccounts::GetEndpointName() const
{
	return TEXT("PutAccounts");
}

UClass* UK2BeamNode_ApiRequest_PutAccounts::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAccounts::GetRequestClass() const
{
	return UPutAccountsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAccounts::GetResponseClass() const
{
	return UAccountsObjectAccount::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutAccounts::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutAccountsSuccess");
}

FString UK2BeamNode_ApiRequest_PutAccounts::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutAccountsError");
}

FString UK2BeamNode_ApiRequest_PutAccounts::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutAccountsComplete");
}

#undef LOCTEXT_NAMESPACE
