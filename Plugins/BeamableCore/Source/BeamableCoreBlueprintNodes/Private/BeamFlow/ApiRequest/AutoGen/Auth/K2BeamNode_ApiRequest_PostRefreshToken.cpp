

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_PostRefreshToken.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostRefreshTokenRequest.h"
#include "BeamableCore/Public/AutoGen/AuthResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostRefreshToken"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostRefreshToken::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostRefreshToken::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, PostRefreshToken);
}

FName UK2BeamNode_ApiRequest_PostRefreshToken::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostRefreshTokenRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostRefreshToken::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_PostRefreshToken::GetEndpointName() const
{
	return TEXT("PostRefreshToken");
}

UClass* UK2BeamNode_ApiRequest_PostRefreshToken::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostRefreshToken::GetRequestClass() const
{
	return UPostRefreshTokenRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostRefreshToken::GetResponseClass() const
{
	return UAuthResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostRefreshToken::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostRefreshTokenSuccess");
}

FString UK2BeamNode_ApiRequest_PostRefreshToken::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostRefreshTokenError");
}

FString UK2BeamNode_ApiRequest_PostRefreshToken::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostRefreshTokenComplete");
}

#undef LOCTEXT_NAMESPACE
