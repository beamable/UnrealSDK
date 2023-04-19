

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/GroupUsers/K2BeamNode_ApiRequest_PostGroup.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupUsersApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/GroupUsers/PostGroupRequest.h"
#include "BeamableCore/Public/AutoGen/GroupCreateResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostGroup"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostGroup::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostGroup::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, PostGroup);
}

FName UK2BeamNode_ApiRequest_PostGroup::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostGroupRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostGroup::GetServiceName() const
{
	return TEXT("GroupUsers");
}

FString UK2BeamNode_ApiRequest_PostGroup::GetEndpointName() const
{
	return TEXT("PostGroup");
}

UClass* UK2BeamNode_ApiRequest_PostGroup::GetApiClass() const
{
	return UBeamGroupUsersApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGroup::GetRequestClass() const
{
	return UPostGroupRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGroup::GetResponseClass() const
{
	return UGroupCreateResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostGroup::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostGroupSuccess");
}

FString UK2BeamNode_ApiRequest_PostGroup::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostGroupError");
}

FString UK2BeamNode_ApiRequest_PostGroup::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostGroupComplete");
}

#undef LOCTEXT_NAMESPACE
