

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_DeleteAdminScope.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/DeleteAdminScopeRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteAdminScope"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteAdminScope::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteAdminScope::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, DeleteAdminScope);
}

FName UK2BeamNode_ApiRequest_DeleteAdminScope::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteAdminScopeRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteAdminScope::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_DeleteAdminScope::GetEndpointName() const
{
	return TEXT("DeleteAdminScope");
}

UClass* UK2BeamNode_ApiRequest_DeleteAdminScope::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteAdminScope::GetRequestClass() const
{
	return UDeleteAdminScopeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteAdminScope::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteAdminScope::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteAdminScopeSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteAdminScope::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteAdminScopeError");
}

FString UK2BeamNode_ApiRequest_DeleteAdminScope::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteAdminScopeComplete");
}

#undef LOCTEXT_NAMESPACE
