

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_DeleteFreeze.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/DeleteFreezeRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteFreeze"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteFreeze::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteFreeze::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, DeleteFreeze);
}

FName UK2BeamNode_ApiRequest_DeleteFreeze::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteFreezeRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteFreeze::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_DeleteFreeze::GetEndpointName() const
{
	return TEXT("DeleteFreeze");
}

UClass* UK2BeamNode_ApiRequest_DeleteFreeze::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteFreeze::GetRequestClass() const
{
	return UDeleteFreezeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteFreeze::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteFreeze::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteFreezeSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteFreeze::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteFreezeError");
}

FString UK2BeamNode_ApiRequest_DeleteFreeze::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteFreezeComplete");
}

#undef LOCTEXT_NAMESPACE
