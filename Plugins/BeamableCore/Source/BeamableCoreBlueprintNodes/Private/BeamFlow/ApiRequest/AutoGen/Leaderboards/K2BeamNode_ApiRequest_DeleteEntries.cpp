

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_DeleteEntries.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/DeleteEntriesRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteEntries"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteEntries::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteEntries::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, DeleteEntries);
}

FName UK2BeamNode_ApiRequest_DeleteEntries::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteEntriesRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteEntries::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_DeleteEntries::GetEndpointName() const
{
	return TEXT("DeleteEntries");
}

UClass* UK2BeamNode_ApiRequest_DeleteEntries::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteEntries::GetRequestClass() const
{
	return UDeleteEntriesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteEntries::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteEntries::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteEntriesSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteEntries::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteEntriesError");
}

FString UK2BeamNode_ApiRequest_DeleteEntries::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteEntriesComplete");
}

#undef LOCTEXT_NAMESPACE
