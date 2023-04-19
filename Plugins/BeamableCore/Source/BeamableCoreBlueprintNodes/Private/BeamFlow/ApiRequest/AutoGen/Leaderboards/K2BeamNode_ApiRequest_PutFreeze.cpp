

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_PutFreeze.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/PutFreezeRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutFreeze"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutFreeze::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutFreeze::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, PutFreeze);
}

FName UK2BeamNode_ApiRequest_PutFreeze::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutFreezeRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutFreeze::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_PutFreeze::GetEndpointName() const
{
	return TEXT("PutFreeze");
}

UClass* UK2BeamNode_ApiRequest_PutFreeze::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutFreeze::GetRequestClass() const
{
	return UPutFreezeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutFreeze::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutFreeze::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutFreezeSuccess");
}

FString UK2BeamNode_ApiRequest_PutFreeze::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutFreezeError");
}

FString UK2BeamNode_ApiRequest_PutFreeze::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutFreezeComplete");
}

#undef LOCTEXT_NAMESPACE
