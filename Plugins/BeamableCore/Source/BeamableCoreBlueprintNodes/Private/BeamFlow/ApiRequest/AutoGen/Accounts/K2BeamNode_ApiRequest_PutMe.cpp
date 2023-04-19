

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PutMe.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PutMeRequest.h"
#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutMe"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutMe::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutMe::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PutMe);
}

FName UK2BeamNode_ApiRequest_PutMe::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutMeRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutMe::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PutMe::GetEndpointName() const
{
	return TEXT("PutMe");
}

UClass* UK2BeamNode_ApiRequest_PutMe::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutMe::GetRequestClass() const
{
	return UPutMeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutMe::GetResponseClass() const
{
	return UAccountPlayerView::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutMe::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutMeSuccess");
}

FString UK2BeamNode_ApiRequest_PutMe::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutMeError");
}

FString UK2BeamNode_ApiRequest_PutMe::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutMeComplete");
}

#undef LOCTEXT_NAMESPACE
