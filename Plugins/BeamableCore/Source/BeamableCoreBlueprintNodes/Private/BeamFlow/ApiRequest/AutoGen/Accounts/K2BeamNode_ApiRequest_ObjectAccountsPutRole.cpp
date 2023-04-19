

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_ObjectAccountsPutRole.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/ObjectAccountsPutRoleRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectAccountsPutRole"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectAccountsPutRole::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectAccountsPutRole::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PutRole);
}

FName UK2BeamNode_ApiRequest_ObjectAccountsPutRole::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectAccountsPutRoleRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectAccountsPutRole::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_ObjectAccountsPutRole::GetEndpointName() const
{
	return TEXT("PutRole");
}

UClass* UK2BeamNode_ApiRequest_ObjectAccountsPutRole::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectAccountsPutRole::GetRequestClass() const
{
	return UObjectAccountsPutRoleRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectAccountsPutRole::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectAccountsPutRole::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectAccountsPutRoleSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectAccountsPutRole::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectAccountsPutRoleError");
}

FString UK2BeamNode_ApiRequest_ObjectAccountsPutRole::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectAccountsPutRoleComplete");
}

#undef LOCTEXT_NAMESPACE
