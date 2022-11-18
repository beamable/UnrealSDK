

#include "BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PostExternal_identity.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamAccountsApi.h"
#include "AutoGen/SubSystems/Accounts/PostExternal_identityRequest.h"
#include "AutoGen/AttachExternalIdentityApiResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostExternal_identity"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostExternal_identity::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostExternal_identity::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PostExternal_identity);
}

FName UK2BeamNode_ApiRequest_PostExternal_identity::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostExternal_identityRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostExternal_identity::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PostExternal_identity::GetEndpointName() const
{
	return TEXT("PostExternal_identity");
}

UClass* UK2BeamNode_ApiRequest_PostExternal_identity::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostExternal_identity::GetRequestClass() const
{
	return UPostExternal_identityRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostExternal_identity::GetResponseClass() const
{
	return UAttachExternalIdentityApiResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostExternal_identity::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostExternal_identitySuccess");
}

FString UK2BeamNode_ApiRequest_PostExternal_identity::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostExternal_identityError");
}

FString UK2BeamNode_ApiRequest_PostExternal_identity::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostExternal_identityComplete");
}

#undef LOCTEXT_NAMESPACE
