

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_PostTokensPassword.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostTokensPasswordRequest.h"
#include "BeamableCore/Public/AutoGen/AuthResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTokensPassword"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTokensPassword::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTokensPassword::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, PostTokensPassword);
}

FName UK2BeamNode_ApiRequest_PostTokensPassword::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTokensPasswordRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTokensPassword::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_PostTokensPassword::GetEndpointName() const
{
	return TEXT("PostTokensPassword");
}

UClass* UK2BeamNode_ApiRequest_PostTokensPassword::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTokensPassword::GetRequestClass() const
{
	return UPostTokensPasswordRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTokensPassword::GetResponseClass() const
{
	return UAuthResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTokensPassword::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTokensPasswordSuccess");
}

FString UK2BeamNode_ApiRequest_PostTokensPassword::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTokensPasswordError");
}

FString UK2BeamNode_ApiRequest_PostTokensPassword::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTokensPasswordComplete");
}

#undef LOCTEXT_NAMESPACE
