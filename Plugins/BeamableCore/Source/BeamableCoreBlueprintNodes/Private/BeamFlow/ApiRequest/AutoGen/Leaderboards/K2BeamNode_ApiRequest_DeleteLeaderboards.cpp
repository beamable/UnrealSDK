

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_DeleteLeaderboards.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/DeleteLeaderboardsRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteLeaderboards"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteLeaderboards::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteLeaderboards::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, DeleteLeaderboards);
}

FName UK2BeamNode_ApiRequest_DeleteLeaderboards::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteLeaderboardsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteLeaderboards::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_DeleteLeaderboards::GetEndpointName() const
{
	return TEXT("DeleteLeaderboards");
}

UClass* UK2BeamNode_ApiRequest_DeleteLeaderboards::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteLeaderboards::GetRequestClass() const
{
	return UDeleteLeaderboardsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteLeaderboards::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteLeaderboards::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteLeaderboardsSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteLeaderboards::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteLeaderboardsError");
}

FString UK2BeamNode_ApiRequest_DeleteLeaderboards::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteLeaderboardsComplete");
}

#undef LOCTEXT_NAMESPACE
