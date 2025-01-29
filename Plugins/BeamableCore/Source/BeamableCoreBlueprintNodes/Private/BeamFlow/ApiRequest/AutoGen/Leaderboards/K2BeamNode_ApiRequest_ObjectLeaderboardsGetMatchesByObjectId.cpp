

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/ObjectLeaderboardsGetMatchesByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/MatchMakingMatchesPvpResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetMatches);
}

FName UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectLeaderboardsGetMatchesByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId::GetEndpointName() const
{
	return TEXT("GetMatches");
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId::GetRequestClass() const
{
	return UObjectLeaderboardsGetMatchesByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId::GetResponseClass() const
{
	return UMatchMakingMatchesPvpResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetMatchesByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetMatchesByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectLeaderboardsGetMatchesByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectLeaderboardsGetMatchesByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
