

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_BasicAccountsPostRegister.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/BasicAccountsPostRegisterRequest.h"
#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicAccountsPostRegister"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicAccountsPostRegister::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicAccountsPostRegister::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PostRegister);
}

FName UK2BeamNode_ApiRequest_BasicAccountsPostRegister::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicAccountsPostRegisterRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicAccountsPostRegister::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_BasicAccountsPostRegister::GetEndpointName() const
{
	return TEXT("PostRegister");
}

UClass* UK2BeamNode_ApiRequest_BasicAccountsPostRegister::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAccountsPostRegister::GetRequestClass() const
{
	return UBasicAccountsPostRegisterRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAccountsPostRegister::GetResponseClass() const
{
	return UAccountPlayerView::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicAccountsPostRegister::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicAccountsPostRegisterSuccess");
}

FString UK2BeamNode_ApiRequest_BasicAccountsPostRegister::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicAccountsPostRegisterError");
}

FString UK2BeamNode_ApiRequest_BasicAccountsPostRegister::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicAccountsPostRegisterComplete");
}

#undef LOCTEXT_NAMESPACE
