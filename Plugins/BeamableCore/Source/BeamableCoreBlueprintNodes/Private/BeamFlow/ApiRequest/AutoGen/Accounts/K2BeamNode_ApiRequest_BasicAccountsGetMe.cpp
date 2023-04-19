

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_BasicAccountsGetMe.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/BasicAccountsGetMeRequest.h"
#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicAccountsGetMe"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicAccountsGetMe::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicAccountsGetMe::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetMe);
}

FName UK2BeamNode_ApiRequest_BasicAccountsGetMe::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicAccountsGetMeRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicAccountsGetMe::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_BasicAccountsGetMe::GetEndpointName() const
{
	return TEXT("GetMe");
}

UClass* UK2BeamNode_ApiRequest_BasicAccountsGetMe::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAccountsGetMe::GetRequestClass() const
{
	return UBasicAccountsGetMeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAccountsGetMe::GetResponseClass() const
{
	return UAccountPlayerView::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicAccountsGetMe::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicAccountsGetMeSuccess");
}

FString UK2BeamNode_ApiRequest_BasicAccountsGetMe::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicAccountsGetMeError");
}

FString UK2BeamNode_ApiRequest_BasicAccountsGetMe::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicAccountsGetMeComplete");
}

#undef LOCTEXT_NAMESPACE
