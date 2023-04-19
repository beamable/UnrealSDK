

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_GetMembership.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetMembershipRequest.h"
#include "BeamableCore/Public/AutoGen/LeaderboardMembershipResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetMembership"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetMembership::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetMembership::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetMembership);
}

FName UK2BeamNode_ApiRequest_GetMembership::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetMembershipRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetMembership::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_GetMembership::GetEndpointName() const
{
	return TEXT("GetMembership");
}

UClass* UK2BeamNode_ApiRequest_GetMembership::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMembership::GetRequestClass() const
{
	return UGetMembershipRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMembership::GetResponseClass() const
{
	return ULeaderboardMembershipResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetMembership::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetMembershipSuccess");
}

FString UK2BeamNode_ApiRequest_GetMembership::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetMembershipError");
}

FString UK2BeamNode_ApiRequest_GetMembership::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetMembershipComplete");
}

#undef LOCTEXT_NAMESPACE
