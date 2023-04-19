

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/BasicLeaderboardsGetAssignmentRequest.h"
#include "BeamableCore/Public/AutoGen/LeaderboardAssignmentInfo.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, BasicLeaderboardsGetAssignment);
}

FName UK2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicLeaderboardsGetAssignmentRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment::GetEndpointName() const
{
	return TEXT("BasicLeaderboardsGetAssignment");
}

UClass* UK2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment::GetRequestClass() const
{
	return UBasicLeaderboardsGetAssignmentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment::GetResponseClass() const
{
	return ULeaderboardAssignmentInfo::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicLeaderboardsGetAssignmentSuccess");
}

FString UK2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicLeaderboardsGetAssignmentError");
}

FString UK2BeamNode_ApiRequest_BasicLeaderboardsGetAssignment::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicLeaderboardsGetAssignmentComplete");
}

#undef LOCTEXT_NAMESPACE
