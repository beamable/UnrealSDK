

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_PutEntry.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/PutEntryRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutEntry"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutEntry::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutEntry::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, PutEntry);
}

FName UK2BeamNode_ApiRequest_PutEntry::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutEntryRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutEntry::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_PutEntry::GetEndpointName() const
{
	return TEXT("PutEntry");
}

UClass* UK2BeamNode_ApiRequest_PutEntry::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutEntry::GetRequestClass() const
{
	return UPutEntryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutEntry::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutEntry::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutEntrySuccess");
}

FString UK2BeamNode_ApiRequest_PutEntry::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutEntryError");
}

FString UK2BeamNode_ApiRequest_PutEntry::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutEntryComplete");
}

#undef LOCTEXT_NAMESPACE
