

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_DeleteExternalIdentity.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/DeleteExternalIdentityRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteExternalIdentity"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteExternalIdentity::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteExternalIdentity::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, DeleteExternalIdentity);
}

FName UK2BeamNode_ApiRequest_DeleteExternalIdentity::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteExternalIdentityRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteExternalIdentity::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_DeleteExternalIdentity::GetEndpointName() const
{
	return TEXT("DeleteExternalIdentity");
}

UClass* UK2BeamNode_ApiRequest_DeleteExternalIdentity::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteExternalIdentity::GetRequestClass() const
{
	return UDeleteExternalIdentityRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteExternalIdentity::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteExternalIdentity::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteExternalIdentitySuccess");
}

FString UK2BeamNode_ApiRequest_DeleteExternalIdentity::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteExternalIdentityError");
}

FString UK2BeamNode_ApiRequest_DeleteExternalIdentity::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteExternalIdentityComplete");
}

#undef LOCTEXT_NAMESPACE
