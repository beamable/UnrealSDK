

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/ObjectGroupsPostInviteByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, PostInvite);
}

FName UK2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectGroupsPostInviteByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId::GetEndpointName() const
{
	return TEXT("PostInvite");
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId::GetRequestClass() const
{
	return UObjectGroupsPostInviteByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectGroupsPostInviteByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectGroupsPostInviteByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPostInviteByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectGroupsPostInviteByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
