

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_GetFind.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetFindRequest.h"
#include "BeamableCore/Public/AutoGen/AccountsBasicAccount.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetFind"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetFind::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetFind::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetFind);
}

FName UK2BeamNode_ApiRequest_GetFind::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetFindRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetFind::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_GetFind::GetEndpointName() const
{
	return TEXT("GetFind");
}

UClass* UK2BeamNode_ApiRequest_GetFind::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetFind::GetRequestClass() const
{
	return UGetFindRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetFind::GetResponseClass() const
{
	return UAccountsBasicAccount::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetFind::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetFindSuccess");
}

FString UK2BeamNode_ApiRequest_GetFind::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetFindError");
}

FString UK2BeamNode_ApiRequest_GetFind::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetFindComplete");
}

#undef LOCTEXT_NAMESPACE
