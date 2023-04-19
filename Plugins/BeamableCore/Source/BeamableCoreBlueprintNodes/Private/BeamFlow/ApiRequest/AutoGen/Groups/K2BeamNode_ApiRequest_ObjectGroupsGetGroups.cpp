

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_ObjectGroupsGetGroups.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/ObjectGroupsGetGroupsRequest.h"
#include "BeamableCore/Public/AutoGen/Group.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectGroupsGetGroups"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectGroupsGetGroups::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectGroupsGetGroups::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetGroups);
}

FName UK2BeamNode_ApiRequest_ObjectGroupsGetGroups::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectGroupsGetGroupsRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectGroupsGetGroups::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsGetGroups::GetEndpointName() const
{
	return TEXT("GetGroups");
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsGetGroups::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsGetGroups::GetRequestClass() const
{
	return UObjectGroupsGetGroupsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsGetGroups::GetResponseClass() const
{
	return UGroup::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectGroupsGetGroups::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectGroupsGetGroupsSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsGetGroups::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectGroupsGetGroupsError");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsGetGroups::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectGroupsGetGroupsComplete");
}

#undef LOCTEXT_NAMESPACE
