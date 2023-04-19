

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_GetAvailableThirdParty.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAvailableThirdPartyRequest.h"
#include "BeamableCore/Public/AutoGen/AccountAvailableResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAvailableThirdParty"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAvailableThirdParty::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAvailableThirdParty::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetAvailableThirdParty);
}

FName UK2BeamNode_ApiRequest_GetAvailableThirdParty::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAvailableThirdPartyRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAvailableThirdParty::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_GetAvailableThirdParty::GetEndpointName() const
{
	return TEXT("GetAvailableThirdParty");
}

UClass* UK2BeamNode_ApiRequest_GetAvailableThirdParty::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailableThirdParty::GetRequestClass() const
{
	return UGetAvailableThirdPartyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailableThirdParty::GetResponseClass() const
{
	return UAccountAvailableResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAvailableThirdParty::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAvailableThirdPartySuccess");
}

FString UK2BeamNode_ApiRequest_GetAvailableThirdParty::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAvailableThirdPartyError");
}

FString UK2BeamNode_ApiRequest_GetAvailableThirdParty::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAvailableThirdPartyComplete");
}

#undef LOCTEXT_NAMESPACE
