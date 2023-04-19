

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_GetMatches.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetMatchesRequest.h"
#include "BeamableCore/Public/AutoGen/MatchMakingMatchesPvpResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetMatches"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetMatches::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetMatches::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetMatches);
}

FName UK2BeamNode_ApiRequest_GetMatches::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetMatchesRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetMatches::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_GetMatches::GetEndpointName() const
{
	return TEXT("GetMatches");
}

UClass* UK2BeamNode_ApiRequest_GetMatches::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMatches::GetRequestClass() const
{
	return UGetMatchesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMatches::GetResponseClass() const
{
	return UMatchMakingMatchesPvpResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetMatches::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetMatchesSuccess");
}

FString UK2BeamNode_ApiRequest_GetMatches::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetMatchesError");
}

FString UK2BeamNode_ApiRequest_GetMatches::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetMatchesComplete");
}

#undef LOCTEXT_NAMESPACE
