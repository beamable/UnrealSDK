

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_Authenticate.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/AuthenticateRequest.h"
#include "BeamableCore/Public/AutoGen/TokenResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_Authenticate"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_Authenticate::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_Authenticate::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, Authenticate);
}

FName UK2BeamNode_ApiRequest_Authenticate::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UAuthenticateRequest, Make);
}

FString UK2BeamNode_ApiRequest_Authenticate::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_Authenticate::GetEndpointName() const
{
	return TEXT("Authenticate");
}

UClass* UK2BeamNode_ApiRequest_Authenticate::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_Authenticate::GetRequestClass() const
{
	return UAuthenticateRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_Authenticate::GetResponseClass() const
{
	return UTokenResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_Authenticate::GetRequestSuccessDelegateName() const
{
	return TEXT("OnAuthenticateSuccess");
}

FString UK2BeamNode_ApiRequest_Authenticate::GetRequestErrorDelegateName() const
{
	return TEXT("OnAuthenticateError");
}

FString UK2BeamNode_ApiRequest_Authenticate::GetRequestCompleteDelegateName() const
{
	return TEXT("OnAuthenticateComplete");
}

#undef LOCTEXT_NAMESPACE
