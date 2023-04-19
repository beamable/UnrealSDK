

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_GetUid.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetUidRequest.h"
#include "BeamableCore/Public/AutoGen/LeaderboardUidResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetUid"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetUid::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetUid::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetUid);
}

FName UK2BeamNode_ApiRequest_GetUid::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetUidRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetUid::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_GetUid::GetEndpointName() const
{
	return TEXT("GetUid");
}

UClass* UK2BeamNode_ApiRequest_GetUid::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetUid::GetRequestClass() const
{
	return UGetUidRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetUid::GetResponseClass() const
{
	return ULeaderboardUidResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetUid::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetUidSuccess");
}

FString UK2BeamNode_ApiRequest_GetUid::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetUidError");
}

FString UK2BeamNode_ApiRequest_GetUid::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetUidComplete");
}

#undef LOCTEXT_NAMESPACE
