

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_BasicLeaderboardsGetList.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/BasicLeaderboardsGetListRequest.h"
#include "BeamableCore/Public/AutoGen/LeaderboardListResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicLeaderboardsGetList"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicLeaderboardsGetList::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicLeaderboardsGetList::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetList);
}

FName UK2BeamNode_ApiRequest_BasicLeaderboardsGetList::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicLeaderboardsGetListRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicLeaderboardsGetList::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_BasicLeaderboardsGetList::GetEndpointName() const
{
	return TEXT("GetList");
}

UClass* UK2BeamNode_ApiRequest_BasicLeaderboardsGetList::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicLeaderboardsGetList::GetRequestClass() const
{
	return UBasicLeaderboardsGetListRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicLeaderboardsGetList::GetResponseClass() const
{
	return ULeaderboardListResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicLeaderboardsGetList::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicLeaderboardsGetListSuccess");
}

FString UK2BeamNode_ApiRequest_BasicLeaderboardsGetList::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicLeaderboardsGetListError");
}

FString UK2BeamNode_ApiRequest_BasicLeaderboardsGetList::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicLeaderboardsGetListComplete");
}

#undef LOCTEXT_NAMESPACE
