

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PostExternalIdentity.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostExternalIdentityRequest.h"
#include "BeamableCore/Public/AutoGen/AttachExternalIdentityApiResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostExternalIdentity"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostExternalIdentity::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostExternalIdentity::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PostExternalIdentity);
}

FName UK2BeamNode_ApiRequest_PostExternalIdentity::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostExternalIdentityRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostExternalIdentity::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PostExternalIdentity::GetEndpointName() const
{
	return TEXT("PostExternalIdentity");
}

UClass* UK2BeamNode_ApiRequest_PostExternalIdentity::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostExternalIdentity::GetRequestClass() const
{
	return UPostExternalIdentityRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostExternalIdentity::GetResponseClass() const
{
	return UAttachExternalIdentityApiResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostExternalIdentity::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostExternalIdentitySuccess");
}

FString UK2BeamNode_ApiRequest_PostExternalIdentity::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostExternalIdentityError");
}

FString UK2BeamNode_ApiRequest_PostExternalIdentity::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostExternalIdentityComplete");
}

#undef LOCTEXT_NAMESPACE
