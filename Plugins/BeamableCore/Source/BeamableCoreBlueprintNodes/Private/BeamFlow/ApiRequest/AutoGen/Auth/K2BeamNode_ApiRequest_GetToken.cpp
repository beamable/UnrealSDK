

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_GetToken.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/GetTokenRequest.h"
#include "BeamableCore/Public/AutoGen/Token.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetToken"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetToken::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetToken::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetToken);
}

FName UK2BeamNode_ApiRequest_GetToken::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetTokenRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetToken::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_GetToken::GetEndpointName() const
{
	return TEXT("GetToken");
}

UClass* UK2BeamNode_ApiRequest_GetToken::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetToken::GetRequestClass() const
{
	return UGetTokenRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetToken::GetResponseClass() const
{
	return UToken::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetToken::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetTokenSuccess");
}

FString UK2BeamNode_ApiRequest_GetToken::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetTokenError");
}

FString UK2BeamNode_ApiRequest_GetToken::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetTokenComplete");
}

#undef LOCTEXT_NAMESPACE
