

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_GetFriends.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetFriendsRequest.h"
#include "BeamableCore/Public/AutoGen/LeaderBoardViewResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetFriends"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetFriends::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetFriends::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetFriends);
}

FName UK2BeamNode_ApiRequest_GetFriends::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetFriendsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetFriends::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_GetFriends::GetEndpointName() const
{
	return TEXT("GetFriends");
}

UClass* UK2BeamNode_ApiRequest_GetFriends::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetFriends::GetRequestClass() const
{
	return UGetFriendsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetFriends::GetResponseClass() const
{
	return ULeaderBoardViewResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetFriends::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetFriendsSuccess");
}

FString UK2BeamNode_ApiRequest_GetFriends::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetFriendsError");
}

FString UK2BeamNode_ApiRequest_GetFriends::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetFriendsComplete");
}

#undef LOCTEXT_NAMESPACE
