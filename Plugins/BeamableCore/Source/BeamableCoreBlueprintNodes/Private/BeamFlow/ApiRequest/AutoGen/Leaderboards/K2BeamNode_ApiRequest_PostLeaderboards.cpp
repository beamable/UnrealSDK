

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_PostLeaderboards.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/PostLeaderboardsRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostLeaderboards"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostLeaderboards::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostLeaderboards::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, PostLeaderboards);
}

FName UK2BeamNode_ApiRequest_PostLeaderboards::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostLeaderboardsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostLeaderboards::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_PostLeaderboards::GetEndpointName() const
{
	return TEXT("PostLeaderboards");
}

UClass* UK2BeamNode_ApiRequest_PostLeaderboards::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostLeaderboards::GetRequestClass() const
{
	return UPostLeaderboardsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostLeaderboards::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostLeaderboards::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostLeaderboardsSuccess");
}

FString UK2BeamNode_ApiRequest_PostLeaderboards::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostLeaderboardsError");
}

FString UK2BeamNode_ApiRequest_PostLeaderboards::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostLeaderboardsComplete");
}

#undef LOCTEXT_NAMESPACE
