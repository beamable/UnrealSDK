

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_GetRoleReport.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetRoleReportRequest.h"
#include "BeamableCore/Public/AutoGen/AccountRolesReport.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRoleReport"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRoleReport::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRoleReport::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetRoleReport);
}

FName UK2BeamNode_ApiRequest_GetRoleReport::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRoleReportRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRoleReport::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_GetRoleReport::GetEndpointName() const
{
	return TEXT("GetRoleReport");
}

UClass* UK2BeamNode_ApiRequest_GetRoleReport::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRoleReport::GetRequestClass() const
{
	return UGetRoleReportRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRoleReport::GetResponseClass() const
{
	return UAccountRolesReport::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRoleReport::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRoleReportSuccess");
}

FString UK2BeamNode_ApiRequest_GetRoleReport::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRoleReportError");
}

FString UK2BeamNode_ApiRequest_GetRoleReport::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRoleReportComplete");
}

#undef LOCTEXT_NAMESPACE
