

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/ObjectLeaderboardsGetAssignmentByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/LeaderboardAssignmentInfo.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, ObjectLeaderboardsGetAssignmentByObjectId);
}

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectLeaderboardsGetAssignmentByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId::GetEndpointName() const
{
	return TEXT("ObjectLeaderboardsGetAssignmentByObjectId");
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId::GetRequestClass() const
{
	return UObjectLeaderboardsGetAssignmentByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId::GetResponseClass() const
{
	return ULeaderboardAssignmentInfo::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetAssignmentByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetAssignmentByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetAssignmentByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetAssignmentByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
