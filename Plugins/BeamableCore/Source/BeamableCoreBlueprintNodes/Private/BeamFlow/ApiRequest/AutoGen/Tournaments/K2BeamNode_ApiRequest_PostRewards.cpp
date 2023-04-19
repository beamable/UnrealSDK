

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_PostRewards.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/PostRewardsRequest.h"
#include "BeamableCore/Public/AutoGen/RewardsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostRewards"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostRewards::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostRewards::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, PostRewards);
}

FName UK2BeamNode_ApiRequest_PostRewards::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostRewardsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostRewards::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_PostRewards::GetEndpointName() const
{
	return TEXT("PostRewards");
}

UClass* UK2BeamNode_ApiRequest_PostRewards::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostRewards::GetRequestClass() const
{
	return UPostRewardsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostRewards::GetResponseClass() const
{
	return URewardsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostRewards::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostRewardsSuccess");
}

FString UK2BeamNode_ApiRequest_PostRewards::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostRewardsError");
}

FString UK2BeamNode_ApiRequest_PostRewards::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostRewardsComplete");
}

#undef LOCTEXT_NAMESPACE
