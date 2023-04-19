

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_GetRewards.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/GetRewardsRequest.h"
#include "BeamableCore/Public/AutoGen/RewardsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRewards"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRewards::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRewards::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetRewards);
}

FName UK2BeamNode_ApiRequest_GetRewards::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRewardsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRewards::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_GetRewards::GetEndpointName() const
{
	return TEXT("GetRewards");
}

UClass* UK2BeamNode_ApiRequest_GetRewards::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRewards::GetRequestClass() const
{
	return UGetRewardsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRewards::GetResponseClass() const
{
	return URewardsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRewards::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRewardsSuccess");
}

FString UK2BeamNode_ApiRequest_GetRewards::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRewardsError");
}

FString UK2BeamNode_ApiRequest_GetRewards::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRewardsComplete");
}

#undef LOCTEXT_NAMESPACE
