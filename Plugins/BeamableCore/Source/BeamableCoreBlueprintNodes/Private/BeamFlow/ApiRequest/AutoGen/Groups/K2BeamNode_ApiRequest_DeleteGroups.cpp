

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_DeleteGroups.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/DeleteGroupsRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteGroups"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteGroups::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteGroups::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, DeleteGroups);
}

FName UK2BeamNode_ApiRequest_DeleteGroups::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteGroupsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteGroups::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_DeleteGroups::GetEndpointName() const
{
	return TEXT("DeleteGroups");
}

UClass* UK2BeamNode_ApiRequest_DeleteGroups::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteGroups::GetRequestClass() const
{
	return UDeleteGroupsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteGroups::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteGroups::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteGroupsSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteGroups::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteGroupsError");
}

FString UK2BeamNode_ApiRequest_DeleteGroups::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteGroupsComplete");
}

#undef LOCTEXT_NAMESPACE
