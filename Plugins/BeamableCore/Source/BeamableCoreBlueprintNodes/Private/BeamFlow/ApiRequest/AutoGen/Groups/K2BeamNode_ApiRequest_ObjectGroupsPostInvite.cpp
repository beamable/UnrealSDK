

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_ObjectGroupsPostInvite.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/ObjectGroupsPostInviteRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectGroupsPostInvite"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectGroupsPostInvite::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectGroupsPostInvite::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, PostInvite);
}

FName UK2BeamNode_ApiRequest_ObjectGroupsPostInvite::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectGroupsPostInviteRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPostInvite::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPostInvite::GetEndpointName() const
{
	return TEXT("PostInvite");
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsPostInvite::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsPostInvite::GetRequestClass() const
{
	return UObjectGroupsPostInviteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsPostInvite::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPostInvite::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectGroupsPostInviteSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPostInvite::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectGroupsPostInviteError");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPostInvite::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectGroupsPostInviteComplete");
}

#undef LOCTEXT_NAMESPACE
