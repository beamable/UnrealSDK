

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_DeleteMeThirdParty.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/DeleteMeThirdPartyRequest.h"
#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteMeThirdParty"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteMeThirdParty::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteMeThirdParty::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, DeleteMeThirdParty);
}

FName UK2BeamNode_ApiRequest_DeleteMeThirdParty::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteMeThirdPartyRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteMeThirdParty::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_DeleteMeThirdParty::GetEndpointName() const
{
	return TEXT("DeleteMeThirdParty");
}

UClass* UK2BeamNode_ApiRequest_DeleteMeThirdParty::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteMeThirdParty::GetRequestClass() const
{
	return UDeleteMeThirdPartyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteMeThirdParty::GetResponseClass() const
{
	return UAccountPlayerView::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteMeThirdParty::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteMeThirdPartySuccess");
}

FString UK2BeamNode_ApiRequest_DeleteMeThirdParty::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteMeThirdPartyError");
}

FString UK2BeamNode_ApiRequest_DeleteMeThirdParty::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteMeThirdPartyComplete");
}

#undef LOCTEXT_NAMESPACE
