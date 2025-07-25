

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PostSignup.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostSignupRequest.h"
#include "BeamableCore/Public/AutoGen/CreateAccountWithCredsApiResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSignup"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSignup::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSignup::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PostSignup);
}

FName UK2BeamNode_ApiRequest_PostSignup::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSignupRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSignup::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PostSignup::GetEndpointName() const
{
	return TEXT("PostSignup");
}

UClass* UK2BeamNode_ApiRequest_PostSignup::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSignup::GetRequestClass() const
{
	return UPostSignupRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSignup::GetResponseClass() const
{
	return UCreateAccountWithCredsApiResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSignup::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSignupSuccess");
}

FString UK2BeamNode_ApiRequest_PostSignup::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSignupError");
}

FString UK2BeamNode_ApiRequest_PostSignup::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSignupComplete");
}

#undef LOCTEXT_NAMESPACE
