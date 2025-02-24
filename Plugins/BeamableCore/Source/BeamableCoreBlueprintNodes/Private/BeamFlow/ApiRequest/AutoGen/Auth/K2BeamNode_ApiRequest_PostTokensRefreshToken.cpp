

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_PostTokensRefreshToken.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostTokensRefreshTokenRequest.h"
#include "BeamableCore/Public/AutoGen/AuthResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTokensRefreshToken"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTokensRefreshToken::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTokensRefreshToken::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, PostTokensRefreshToken);
}

FName UK2BeamNode_ApiRequest_PostTokensRefreshToken::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTokensRefreshTokenRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTokensRefreshToken::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_PostTokensRefreshToken::GetEndpointName() const
{
	return TEXT("PostTokensRefreshToken");
}

UClass* UK2BeamNode_ApiRequest_PostTokensRefreshToken::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTokensRefreshToken::GetRequestClass() const
{
	return UPostTokensRefreshTokenRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTokensRefreshToken::GetResponseClass() const
{
	return UAuthResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTokensRefreshToken::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTokensRefreshTokenSuccess");
}

FString UK2BeamNode_ApiRequest_PostTokensRefreshToken::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTokensRefreshTokenError");
}

FString UK2BeamNode_ApiRequest_PostTokensRefreshToken::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTokensRefreshTokenComplete");
}

#undef LOCTEXT_NAMESPACE
