

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_DeleteAdminThirdParty.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/DeleteAdminThirdPartyRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteAdminThirdParty"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteAdminThirdParty::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteAdminThirdParty::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, DeleteAdminThirdParty);
}

FName UK2BeamNode_ApiRequest_DeleteAdminThirdParty::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteAdminThirdPartyRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteAdminThirdParty::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_DeleteAdminThirdParty::GetEndpointName() const
{
	return TEXT("DeleteAdminThirdParty");
}

UClass* UK2BeamNode_ApiRequest_DeleteAdminThirdParty::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteAdminThirdParty::GetRequestClass() const
{
	return UDeleteAdminThirdPartyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteAdminThirdParty::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteAdminThirdParty::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteAdminThirdPartySuccess");
}

FString UK2BeamNode_ApiRequest_DeleteAdminThirdParty::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteAdminThirdPartyError");
}

FString UK2BeamNode_ApiRequest_DeleteAdminThirdParty::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteAdminThirdPartyComplete");
}

#undef LOCTEXT_NAMESPACE
