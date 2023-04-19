

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PutAdminScope.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PutAdminScopeRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutAdminScope"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutAdminScope::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutAdminScope::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PutAdminScope);
}

FName UK2BeamNode_ApiRequest_PutAdminScope::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutAdminScopeRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutAdminScope::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PutAdminScope::GetEndpointName() const
{
	return TEXT("PutAdminScope");
}

UClass* UK2BeamNode_ApiRequest_PutAdminScope::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAdminScope::GetRequestClass() const
{
	return UPutAdminScopeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAdminScope::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutAdminScope::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutAdminScopeSuccess");
}

FString UK2BeamNode_ApiRequest_PutAdminScope::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutAdminScopeError");
}

FString UK2BeamNode_ApiRequest_PutAdminScope::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutAdminScopeComplete");
}

#undef LOCTEXT_NAMESPACE
