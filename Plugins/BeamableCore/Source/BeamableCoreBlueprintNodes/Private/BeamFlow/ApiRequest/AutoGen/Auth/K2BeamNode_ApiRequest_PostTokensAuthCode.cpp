

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_PostTokensAuthCode.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostTokensAuthCodeRequest.h"
#include "BeamableCore/Public/AutoGen/AuthV2AuthResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTokensAuthCode"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTokensAuthCode::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTokensAuthCode::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, PostTokensAuthCode);
}

FName UK2BeamNode_ApiRequest_PostTokensAuthCode::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTokensAuthCodeRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTokensAuthCode::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_PostTokensAuthCode::GetEndpointName() const
{
	return TEXT("PostTokensAuthCode");
}

UClass* UK2BeamNode_ApiRequest_PostTokensAuthCode::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTokensAuthCode::GetRequestClass() const
{
	return UPostTokensAuthCodeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTokensAuthCode::GetResponseClass() const
{
	return UAuthV2AuthResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTokensAuthCode::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTokensAuthCodeSuccess");
}

FString UK2BeamNode_ApiRequest_PostTokensAuthCode::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTokensAuthCodeError");
}

FString UK2BeamNode_ApiRequest_PostTokensAuthCode::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTokensAuthCodeComplete");
}

#undef LOCTEXT_NAMESPACE
