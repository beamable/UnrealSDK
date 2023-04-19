

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_GetAdminAdminUsers.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAdminAdminUsersRequest.h"
#include "BeamableCore/Public/AutoGen/GetAdminsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAdminAdminUsers"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAdminAdminUsers::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAdminAdminUsers::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetAdminAdminUsers);
}

FName UK2BeamNode_ApiRequest_GetAdminAdminUsers::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAdminAdminUsersRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAdminAdminUsers::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_GetAdminAdminUsers::GetEndpointName() const
{
	return TEXT("GetAdminAdminUsers");
}

UClass* UK2BeamNode_ApiRequest_GetAdminAdminUsers::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAdminAdminUsers::GetRequestClass() const
{
	return UGetAdminAdminUsersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAdminAdminUsers::GetResponseClass() const
{
	return UGetAdminsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAdminAdminUsers::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAdminAdminUsersSuccess");
}

FString UK2BeamNode_ApiRequest_GetAdminAdminUsers::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAdminAdminUsersError");
}

FString UK2BeamNode_ApiRequest_GetAdminAdminUsers::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAdminAdminUsersComplete");
}

#undef LOCTEXT_NAMESPACE
