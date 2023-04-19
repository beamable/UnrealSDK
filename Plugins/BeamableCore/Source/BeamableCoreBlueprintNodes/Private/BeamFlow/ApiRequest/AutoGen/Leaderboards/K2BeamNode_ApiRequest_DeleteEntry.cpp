

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_DeleteEntry.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/DeleteEntryRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteEntry"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteEntry::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteEntry::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, DeleteEntry);
}

FName UK2BeamNode_ApiRequest_DeleteEntry::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteEntryRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteEntry::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_DeleteEntry::GetEndpointName() const
{
	return TEXT("DeleteEntry");
}

UClass* UK2BeamNode_ApiRequest_DeleteEntry::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteEntry::GetRequestClass() const
{
	return UDeleteEntryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteEntry::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteEntry::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteEntrySuccess");
}

FString UK2BeamNode_ApiRequest_DeleteEntry::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteEntryError");
}

FString UK2BeamNode_ApiRequest_DeleteEntry::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteEntryComplete");
}

#undef LOCTEXT_NAMESPACE
