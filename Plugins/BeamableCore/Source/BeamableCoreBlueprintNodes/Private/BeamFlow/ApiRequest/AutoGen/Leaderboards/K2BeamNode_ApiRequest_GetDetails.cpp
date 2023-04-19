

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_GetDetails.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetDetailsRequest.h"
#include "BeamableCore/Public/AutoGen/LeaderboardDetails.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetDetails"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetDetails::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetDetails::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetDetails);
}

FName UK2BeamNode_ApiRequest_GetDetails::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetDetailsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetDetails::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_GetDetails::GetEndpointName() const
{
	return TEXT("GetDetails");
}

UClass* UK2BeamNode_ApiRequest_GetDetails::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetDetails::GetRequestClass() const
{
	return UGetDetailsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetDetails::GetResponseClass() const
{
	return ULeaderboardDetails::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetDetails::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetDetailsSuccess");
}

FString UK2BeamNode_ApiRequest_GetDetails::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetDetailsError");
}

FString UK2BeamNode_ApiRequest_GetDetails::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetDetailsComplete");
}

#undef LOCTEXT_NAMESPACE
