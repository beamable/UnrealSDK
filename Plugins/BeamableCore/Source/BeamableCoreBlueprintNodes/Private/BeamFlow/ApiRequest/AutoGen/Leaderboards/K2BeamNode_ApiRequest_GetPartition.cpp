

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_GetPartition.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetPartitionRequest.h"
#include "BeamableCore/Public/AutoGen/LeaderboardPartitionInfo.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetPartition"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetPartition::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetPartition::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetPartition);
}

FName UK2BeamNode_ApiRequest_GetPartition::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetPartitionRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetPartition::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_GetPartition::GetEndpointName() const
{
	return TEXT("GetPartition");
}

UClass* UK2BeamNode_ApiRequest_GetPartition::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPartition::GetRequestClass() const
{
	return UGetPartitionRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPartition::GetResponseClass() const
{
	return ULeaderboardPartitionInfo::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetPartition::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetPartitionSuccess");
}

FString UK2BeamNode_ApiRequest_GetPartition::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetPartitionError");
}

FString UK2BeamNode_ApiRequest_GetPartition::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetPartitionComplete");
}

#undef LOCTEXT_NAMESPACE
