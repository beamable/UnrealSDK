

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_GetRanks.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetRanksRequest.h"
#include "BeamableCore/Public/AutoGen/LeaderBoardViewResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRanks"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRanks::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRanks::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetRanks);
}

FName UK2BeamNode_ApiRequest_GetRanks::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRanksRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRanks::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_GetRanks::GetEndpointName() const
{
	return TEXT("GetRanks");
}

UClass* UK2BeamNode_ApiRequest_GetRanks::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRanks::GetRequestClass() const
{
	return UGetRanksRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRanks::GetResponseClass() const
{
	return ULeaderBoardViewResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRanks::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRanksSuccess");
}

FString UK2BeamNode_ApiRequest_GetRanks::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRanksError");
}

FString UK2BeamNode_ApiRequest_GetRanks::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRanksComplete");
}

#undef LOCTEXT_NAMESPACE
