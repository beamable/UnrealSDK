

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/ObjectLeaderboardsGetAssignmentRequest.h"
#include "BeamableCore/Public/AutoGen/LeaderboardAssignmentInfo.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, ObjectLeaderboardsGetAssignment);
}

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectLeaderboardsGetAssignmentRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment::GetEndpointName() const
{
	return TEXT("ObjectLeaderboardsGetAssignment");
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment::GetRequestClass() const
{
	return UObjectLeaderboardsGetAssignmentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment::GetResponseClass() const
{
	return ULeaderboardAssignmentInfo::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetAssignmentSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetAssignmentError");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignment::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetAssignmentComplete");
}

#undef LOCTEXT_NAMESPACE
