

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_GetAvailableRoles.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAvailableRolesRequest.h"
#include "BeamableCore/Public/AutoGen/AvailableRolesResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAvailableRoles"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAvailableRoles::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAvailableRoles::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetAvailableRoles);
}

FName UK2BeamNode_ApiRequest_GetAvailableRoles::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAvailableRolesRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAvailableRoles::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_GetAvailableRoles::GetEndpointName() const
{
	return TEXT("GetAvailableRoles");
}

UClass* UK2BeamNode_ApiRequest_GetAvailableRoles::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailableRoles::GetRequestClass() const
{
	return UGetAvailableRolesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailableRoles::GetResponseClass() const
{
	return UAvailableRolesResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAvailableRoles::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAvailableRolesSuccess");
}

FString UK2BeamNode_ApiRequest_GetAvailableRoles::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAvailableRolesError");
}

FString UK2BeamNode_ApiRequest_GetAvailableRoles::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAvailableRolesComplete");
}

#undef LOCTEXT_NAMESPACE
