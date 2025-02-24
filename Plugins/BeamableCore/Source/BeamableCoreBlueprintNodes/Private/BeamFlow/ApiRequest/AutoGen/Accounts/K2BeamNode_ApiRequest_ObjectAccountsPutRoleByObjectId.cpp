

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/ObjectAccountsPutRoleByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PutRole);
}

FName UK2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectAccountsPutRoleByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId::GetEndpointName() const
{
	return TEXT("PutRole");
}

UClass* UK2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId::GetRequestClass() const
{
	return UObjectAccountsPutRoleByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectAccountsPutRoleByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectAccountsPutRoleByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectAccountsPutRoleByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectAccountsPutRoleByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
