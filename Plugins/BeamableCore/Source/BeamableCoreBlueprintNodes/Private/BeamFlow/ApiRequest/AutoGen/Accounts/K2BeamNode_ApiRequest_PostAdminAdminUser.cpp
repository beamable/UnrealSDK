

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PostAdminAdminUser.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostAdminAdminUserRequest.h"
#include "BeamableCore/Public/AutoGen/AccountPortalView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostAdminAdminUser"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostAdminAdminUser::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostAdminAdminUser::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PostAdminAdminUser);
}

FName UK2BeamNode_ApiRequest_PostAdminAdminUser::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostAdminAdminUserRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostAdminAdminUser::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PostAdminAdminUser::GetEndpointName() const
{
	return TEXT("PostAdminAdminUser");
}

UClass* UK2BeamNode_ApiRequest_PostAdminAdminUser::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostAdminAdminUser::GetRequestClass() const
{
	return UPostAdminAdminUserRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostAdminAdminUser::GetResponseClass() const
{
	return UAccountPortalView::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostAdminAdminUser::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostAdminAdminUserSuccess");
}

FString UK2BeamNode_ApiRequest_PostAdminAdminUser::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostAdminAdminUserError");
}

FString UK2BeamNode_ApiRequest_PostAdminAdminUser::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostAdminAdminUserComplete");
}

#undef LOCTEXT_NAMESPACE
