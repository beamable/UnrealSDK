

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_ObjectGroupsPutRole.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/ObjectGroupsPutRoleRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectGroupsPutRole"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectGroupsPutRole::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectGroupsPutRole::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, PutRole);
}

FName UK2BeamNode_ApiRequest_ObjectGroupsPutRole::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectGroupsPutRoleRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPutRole::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPutRole::GetEndpointName() const
{
	return TEXT("PutRole");
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsPutRole::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsPutRole::GetRequestClass() const
{
	return UObjectGroupsPutRoleRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsPutRole::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPutRole::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectGroupsPutRoleSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPutRole::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectGroupsPutRoleError");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPutRole::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectGroupsPutRoleComplete");
}

#undef LOCTEXT_NAMESPACE
