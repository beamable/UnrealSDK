

#include "BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_PostInvite.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamGroupsApi.h"
#include "AutoGen/SubSystems/Groups/PostInviteRequest.h"
#include "AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostInvite"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostInvite::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostInvite::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, PostInvite);
}

FName UK2BeamNode_ApiRequest_PostInvite::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostInviteRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostInvite::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_PostInvite::GetEndpointName() const
{
	return TEXT("PostInvite");
}

UClass* UK2BeamNode_ApiRequest_PostInvite::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostInvite::GetRequestClass() const
{
	return UPostInviteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostInvite::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostInvite::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostInviteSuccess");
}

FString UK2BeamNode_ApiRequest_PostInvite::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostInviteError");
}

FString UK2BeamNode_ApiRequest_PostInvite::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostInviteComplete");
}

#undef LOCTEXT_NAMESPACE
