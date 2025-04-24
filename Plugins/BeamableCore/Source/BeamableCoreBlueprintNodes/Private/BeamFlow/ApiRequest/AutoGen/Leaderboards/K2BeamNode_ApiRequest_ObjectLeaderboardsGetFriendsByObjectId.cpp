

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/ObjectLeaderboardsGetFriendsByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/LeaderBoardViewResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetFriends);
}

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectLeaderboardsGetFriendsByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId::GetEndpointName() const
{
	return TEXT("GetFriends");
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId::GetRequestClass() const
{
	return UObjectLeaderboardsGetFriendsByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId::GetResponseClass() const
{
	return ULeaderBoardViewResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetFriendsByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetFriendsByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetFriendsByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetFriendsByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
