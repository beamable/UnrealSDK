

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_PutSwap.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/PutSwapRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutSwap"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutSwap::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutSwap::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, PutSwap);
}

FName UK2BeamNode_ApiRequest_PutSwap::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutSwapRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutSwap::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_PutSwap::GetEndpointName() const
{
	return TEXT("PutSwap");
}

UClass* UK2BeamNode_ApiRequest_PutSwap::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutSwap::GetRequestClass() const
{
	return UPutSwapRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutSwap::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutSwap::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutSwapSuccess");
}

FString UK2BeamNode_ApiRequest_PutSwap::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutSwapError");
}

FString UK2BeamNode_ApiRequest_PutSwap::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutSwapComplete");
}

#undef LOCTEXT_NAMESPACE
