

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_BasicAccountsGetSearch.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/BasicAccountsGetSearchRequest.h"
#include "BeamableCore/Public/AutoGen/AccountSearchResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicAccountsGetSearch"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicAccountsGetSearch::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicAccountsGetSearch::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSearch);
}

FName UK2BeamNode_ApiRequest_BasicAccountsGetSearch::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicAccountsGetSearchRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicAccountsGetSearch::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_BasicAccountsGetSearch::GetEndpointName() const
{
	return TEXT("GetSearch");
}

UClass* UK2BeamNode_ApiRequest_BasicAccountsGetSearch::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAccountsGetSearch::GetRequestClass() const
{
	return UBasicAccountsGetSearchRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAccountsGetSearch::GetResponseClass() const
{
	return UAccountSearchResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicAccountsGetSearch::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicAccountsGetSearchSuccess");
}

FString UK2BeamNode_ApiRequest_BasicAccountsGetSearch::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicAccountsGetSearchError");
}

FString UK2BeamNode_ApiRequest_BasicAccountsGetSearch::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicAccountsGetSearchComplete");
}

#undef LOCTEXT_NAMESPACE
