

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_GetAdminMe.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAdminMeRequest.h"
#include "BeamableCore/Public/AutoGen/AccountPortalView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAdminMe"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAdminMe::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAdminMe::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetAdminMe);
}

FName UK2BeamNode_ApiRequest_GetAdminMe::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAdminMeRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAdminMe::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_GetAdminMe::GetEndpointName() const
{
	return TEXT("GetAdminMe");
}

UClass* UK2BeamNode_ApiRequest_GetAdminMe::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAdminMe::GetRequestClass() const
{
	return UGetAdminMeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAdminMe::GetResponseClass() const
{
	return UAccountPortalView::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAdminMe::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAdminMeSuccess");
}

FString UK2BeamNode_ApiRequest_GetAdminMe::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAdminMeError");
}

FString UK2BeamNode_ApiRequest_GetAdminMe::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAdminMeComplete");
}

#undef LOCTEXT_NAMESPACE
