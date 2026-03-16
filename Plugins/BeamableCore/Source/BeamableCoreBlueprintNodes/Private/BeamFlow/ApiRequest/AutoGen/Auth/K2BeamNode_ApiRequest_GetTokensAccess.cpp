

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_GetTokensAccess.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/GetTokensAccessRequest.h"
#include "BeamableCore/Public/AutoGen/AuthV2LegacyAccessToken.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetTokensAccess"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetTokensAccess::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetTokensAccess::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetTokensAccess);
}

FName UK2BeamNode_ApiRequest_GetTokensAccess::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetTokensAccessRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetTokensAccess::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_GetTokensAccess::GetEndpointName() const
{
	return TEXT("GetTokensAccess");
}

UClass* UK2BeamNode_ApiRequest_GetTokensAccess::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetTokensAccess::GetRequestClass() const
{
	return UGetTokensAccessRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetTokensAccess::GetResponseClass() const
{
	return UAuthV2LegacyAccessToken::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetTokensAccess::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetTokensAccessSuccess");
}

FString UK2BeamNode_ApiRequest_GetTokensAccess::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetTokensAccessError");
}

FString UK2BeamNode_ApiRequest_GetTokensAccess::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetTokensAccessComplete");
}

#undef LOCTEXT_NAMESPACE
