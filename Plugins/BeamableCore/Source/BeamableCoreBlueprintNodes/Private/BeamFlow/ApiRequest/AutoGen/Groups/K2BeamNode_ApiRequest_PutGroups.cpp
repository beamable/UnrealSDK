

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_PutGroups.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/PutGroupsRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutGroups"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutGroups::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutGroups::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, PutGroups);
}

FName UK2BeamNode_ApiRequest_PutGroups::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutGroupsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutGroups::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_PutGroups::GetEndpointName() const
{
	return TEXT("PutGroups");
}

UClass* UK2BeamNode_ApiRequest_PutGroups::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutGroups::GetRequestClass() const
{
	return UPutGroupsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutGroups::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutGroups::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutGroupsSuccess");
}

FString UK2BeamNode_ApiRequest_PutGroups::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutGroupsError");
}

FString UK2BeamNode_ApiRequest_PutGroups::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutGroupsComplete");
}

#undef LOCTEXT_NAMESPACE
