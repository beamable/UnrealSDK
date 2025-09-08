

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PostSignupVerify.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostSignupVerifyRequest.h"
#include "BeamableCore/Public/AutoGen/SignupVerificationResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSignupVerify"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSignupVerify::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSignupVerify::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PostSignupVerify);
}

FName UK2BeamNode_ApiRequest_PostSignupVerify::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSignupVerifyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSignupVerify::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PostSignupVerify::GetEndpointName() const
{
	return TEXT("PostSignupVerify");
}

UClass* UK2BeamNode_ApiRequest_PostSignupVerify::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSignupVerify::GetRequestClass() const
{
	return UPostSignupVerifyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSignupVerify::GetResponseClass() const
{
	return USignupVerificationResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSignupVerify::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSignupVerifySuccess");
}

FString UK2BeamNode_ApiRequest_PostSignupVerify::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSignupVerifyError");
}

FString UK2BeamNode_ApiRequest_PostSignupVerify::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSignupVerifyComplete");
}

#undef LOCTEXT_NAMESPACE
