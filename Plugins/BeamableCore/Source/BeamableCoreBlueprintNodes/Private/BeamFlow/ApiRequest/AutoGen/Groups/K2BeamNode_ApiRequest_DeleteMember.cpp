

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_DeleteMember.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/DeleteMemberRequest.h"
#include "BeamableCore/Public/AutoGen/GroupMembershipResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteMember"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteMember::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteMember::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, DeleteMember);
}

FName UK2BeamNode_ApiRequest_DeleteMember::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteMemberRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteMember::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_DeleteMember::GetEndpointName() const
{
	return TEXT("DeleteMember");
}

UClass* UK2BeamNode_ApiRequest_DeleteMember::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteMember::GetRequestClass() const
{
	return UDeleteMemberRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteMember::GetResponseClass() const
{
	return UGroupMembershipResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteMember::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteMemberSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteMember::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteMemberError");
}

FString UK2BeamNode_ApiRequest_DeleteMember::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteMemberComplete");
}

#undef LOCTEXT_NAMESPACE
