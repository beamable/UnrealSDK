

#include "BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_GetAvailableExternal_identity.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamAccountsApi.h"
#include "AutoGen/SubSystems/Accounts/GetAvailableExternal_identityRequest.h"
#include "AutoGen/AccountAvailableResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAvailableExternal_identity"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAvailableExternal_identity::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAvailableExternal_identity::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetAvailableExternal_identity);
}

FName UK2BeamNode_ApiRequest_GetAvailableExternal_identity::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAvailableExternal_identityRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAvailableExternal_identity::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_GetAvailableExternal_identity::GetEndpointName() const
{
	return TEXT("GetAvailableExternal_identity");
}

UClass* UK2BeamNode_ApiRequest_GetAvailableExternal_identity::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailableExternal_identity::GetRequestClass() const
{
	return UGetAvailableExternal_identityRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailableExternal_identity::GetResponseClass() const
{
	return UAccountAvailableResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAvailableExternal_identity::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAvailableExternal_identitySuccess");
}

FString UK2BeamNode_ApiRequest_GetAvailableExternal_identity::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAvailableExternal_identityError");
}

FString UK2BeamNode_ApiRequest_GetAvailableExternal_identity::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAvailableExternal_identityComplete");
}

#undef LOCTEXT_NAMESPACE
