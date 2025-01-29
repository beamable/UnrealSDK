

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/ObjectGroupsGetGroupsByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/Group.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetGroups);
}

FName UK2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectGroupsGetGroupsByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId::GetEndpointName() const
{
	return TEXT("GetGroups");
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId::GetRequestClass() const
{
	return UObjectGroupsGetGroupsByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId::GetResponseClass() const
{
	return UGroup::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectGroupsGetGroupsByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectGroupsGetGroupsByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsGetGroupsByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectGroupsGetGroupsByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
