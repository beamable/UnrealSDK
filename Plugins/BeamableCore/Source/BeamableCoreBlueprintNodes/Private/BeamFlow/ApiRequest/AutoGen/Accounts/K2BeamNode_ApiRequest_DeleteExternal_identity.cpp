

#include "BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_DeleteExternal_identity.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamAccountsApi.h"
#include "AutoGen/SubSystems/Accounts/DeleteExternal_identityRequest.h"
#include "AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteExternal_identity"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteExternal_identity::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteExternal_identity::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, DeleteExternal_identity);
}

FName UK2BeamNode_ApiRequest_DeleteExternal_identity::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteExternal_identityRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteExternal_identity::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_DeleteExternal_identity::GetEndpointName() const
{
	return TEXT("DeleteExternal_identity");
}

UClass* UK2BeamNode_ApiRequest_DeleteExternal_identity::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteExternal_identity::GetRequestClass() const
{
	return UDeleteExternal_identityRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteExternal_identity::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteExternal_identity::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteExternal_identitySuccess");
}

FString UK2BeamNode_ApiRequest_DeleteExternal_identity::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteExternal_identityError");
}

FString UK2BeamNode_ApiRequest_DeleteExternal_identity::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteExternal_identityComplete");
}

#undef LOCTEXT_NAMESPACE
