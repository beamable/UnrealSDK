

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PutAdminThirdParty.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PutAdminThirdPartyRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutAdminThirdParty"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutAdminThirdParty::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutAdminThirdParty::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PutAdminThirdParty);
}

FName UK2BeamNode_ApiRequest_PutAdminThirdParty::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutAdminThirdPartyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutAdminThirdParty::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PutAdminThirdParty::GetEndpointName() const
{
	return TEXT("PutAdminThirdParty");
}

UClass* UK2BeamNode_ApiRequest_PutAdminThirdParty::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAdminThirdParty::GetRequestClass() const
{
	return UPutAdminThirdPartyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAdminThirdParty::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutAdminThirdParty::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutAdminThirdPartySuccess");
}

FString UK2BeamNode_ApiRequest_PutAdminThirdParty::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutAdminThirdPartyError");
}

FString UK2BeamNode_ApiRequest_PutAdminThirdParty::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutAdminThirdPartyComplete");
}

#undef LOCTEXT_NAMESPACE
