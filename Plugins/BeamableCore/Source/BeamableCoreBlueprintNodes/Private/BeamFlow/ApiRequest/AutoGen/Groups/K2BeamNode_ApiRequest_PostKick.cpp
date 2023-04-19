

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_PostKick.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/PostKickRequest.h"
#include "BeamableCore/Public/AutoGen/GroupMembershipResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostKick"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostKick::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostKick::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, PostKick);
}

FName UK2BeamNode_ApiRequest_PostKick::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostKickRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostKick::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_PostKick::GetEndpointName() const
{
	return TEXT("PostKick");
}

UClass* UK2BeamNode_ApiRequest_PostKick::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostKick::GetRequestClass() const
{
	return UPostKickRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostKick::GetResponseClass() const
{
	return UGroupMembershipResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostKick::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostKickSuccess");
}

FString UK2BeamNode_ApiRequest_PostKick::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostKickError");
}

FString UK2BeamNode_ApiRequest_PostKick::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostKickComplete");
}

#undef LOCTEXT_NAMESPACE
