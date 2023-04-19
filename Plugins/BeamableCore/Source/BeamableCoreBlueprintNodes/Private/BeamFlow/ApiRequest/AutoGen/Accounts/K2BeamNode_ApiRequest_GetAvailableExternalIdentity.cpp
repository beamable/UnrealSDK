

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_GetAvailableExternalIdentity.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAvailableExternalIdentityRequest.h"
#include "BeamableCore/Public/AutoGen/AccountAvailableResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAvailableExternalIdentity"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAvailableExternalIdentity::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAvailableExternalIdentity::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetAvailableExternalIdentity);
}

FName UK2BeamNode_ApiRequest_GetAvailableExternalIdentity::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAvailableExternalIdentityRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAvailableExternalIdentity::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_GetAvailableExternalIdentity::GetEndpointName() const
{
	return TEXT("GetAvailableExternalIdentity");
}

UClass* UK2BeamNode_ApiRequest_GetAvailableExternalIdentity::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailableExternalIdentity::GetRequestClass() const
{
	return UGetAvailableExternalIdentityRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailableExternalIdentity::GetResponseClass() const
{
	return UAccountAvailableResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAvailableExternalIdentity::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAvailableExternalIdentitySuccess");
}

FString UK2BeamNode_ApiRequest_GetAvailableExternalIdentity::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAvailableExternalIdentityError");
}

FString UK2BeamNode_ApiRequest_GetAvailableExternalIdentity::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAvailableExternalIdentityComplete");
}

#undef LOCTEXT_NAMESPACE
