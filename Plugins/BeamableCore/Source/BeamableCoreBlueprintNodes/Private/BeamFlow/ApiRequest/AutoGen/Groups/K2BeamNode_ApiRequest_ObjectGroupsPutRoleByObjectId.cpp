

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/ObjectGroupsPutRoleByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, PutRole);
}

FName UK2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectGroupsPutRoleByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId::GetEndpointName() const
{
	return TEXT("PutRole");
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId::GetRequestClass() const
{
	return UObjectGroupsPutRoleByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectGroupsPutRoleByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectGroupsPutRoleByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectGroupsPutRoleByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectGroupsPutRoleByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
