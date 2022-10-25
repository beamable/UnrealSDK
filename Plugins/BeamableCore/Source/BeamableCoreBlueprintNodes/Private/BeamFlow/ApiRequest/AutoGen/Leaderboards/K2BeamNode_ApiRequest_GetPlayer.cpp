

#include "BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_GetPlayer.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "AutoGen/SubSystems/Leaderboards/GetPlayerRequest.h"
#include "AutoGen/ListLeaderBoardViewResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetPlayer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetPlayer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetPlayer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetPlayer);
}

FName UK2BeamNode_ApiRequest_GetPlayer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetPlayerRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetPlayer::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_GetPlayer::GetEndpointName() const
{
	return TEXT("GetPlayer");
}

UClass* UK2BeamNode_ApiRequest_GetPlayer::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPlayer::GetRequestClass() const
{
	return UGetPlayerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPlayer::GetResponseClass() const
{
	return UListLeaderBoardViewResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetPlayer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetPlayerSuccess");
}

FString UK2BeamNode_ApiRequest_GetPlayer::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetPlayerError");
}

FString UK2BeamNode_ApiRequest_GetPlayer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetPlayerComplete");
}

#undef LOCTEXT_NAMESPACE
