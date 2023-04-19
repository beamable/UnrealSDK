

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_PostSearchGroups.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/PostSearchGroupsRequest.h"
#include "BeamableCore/Public/AutoGen/GetStatusForGroupsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSearchGroups"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSearchGroups::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSearchGroups::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, PostSearchGroups);
}

FName UK2BeamNode_ApiRequest_PostSearchGroups::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSearchGroupsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSearchGroups::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_PostSearchGroups::GetEndpointName() const
{
	return TEXT("PostSearchGroups");
}

UClass* UK2BeamNode_ApiRequest_PostSearchGroups::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSearchGroups::GetRequestClass() const
{
	return UPostSearchGroupsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSearchGroups::GetResponseClass() const
{
	return UGetStatusForGroupsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSearchGroups::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSearchGroupsSuccess");
}

FString UK2BeamNode_ApiRequest_PostSearchGroups::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSearchGroupsError");
}

FString UK2BeamNode_ApiRequest_PostSearchGroups::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSearchGroupsComplete");
}

#undef LOCTEXT_NAMESPACE
