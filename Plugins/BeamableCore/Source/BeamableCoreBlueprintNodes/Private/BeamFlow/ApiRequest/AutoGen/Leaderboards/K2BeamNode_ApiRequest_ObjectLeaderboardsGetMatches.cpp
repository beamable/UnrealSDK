

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/ObjectLeaderboardsGetMatchesRequest.h"
#include "BeamableCore/Public/AutoGen/MatchMakingMatchesPvpResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetMatches);
}

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectLeaderboardsGetMatchesRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches::GetEndpointName() const
{
	return TEXT("GetMatches");
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches::GetRequestClass() const
{
	return UObjectLeaderboardsGetMatchesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches::GetResponseClass() const
{
	return UMatchMakingMatchesPvpResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetMatchesSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetMatchesError");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatches::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetMatchesComplete");
}

#undef LOCTEXT_NAMESPACE
