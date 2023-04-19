

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_DeleteRole.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/DeleteRoleRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteRole"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteRole::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteRole::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, DeleteRole);
}

FName UK2BeamNode_ApiRequest_DeleteRole::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteRoleRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteRole::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_DeleteRole::GetEndpointName() const
{
	return TEXT("DeleteRole");
}

UClass* UK2BeamNode_ApiRequest_DeleteRole::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteRole::GetRequestClass() const
{
	return UDeleteRoleRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteRole::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteRole::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteRoleSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteRole::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteRoleError");
}

FString UK2BeamNode_ApiRequest_DeleteRole::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteRoleComplete");
}

#undef LOCTEXT_NAMESPACE
