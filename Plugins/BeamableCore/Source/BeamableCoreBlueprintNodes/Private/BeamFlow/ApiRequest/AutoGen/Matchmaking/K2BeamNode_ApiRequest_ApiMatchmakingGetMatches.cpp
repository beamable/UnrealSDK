

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Matchmaking/K2BeamNode_ApiRequest_ApiMatchmakingGetMatches.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/ApiMatchmakingGetMatchesRequest.h"
#include "BeamableCore/Public/AutoGen/Match.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiMatchmakingGetMatches"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiMatchmakingGetMatches::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiMatchmakingGetMatches::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetMatches);
}

FName UK2BeamNode_ApiRequest_ApiMatchmakingGetMatches::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiMatchmakingGetMatchesRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetMatches::GetServiceName() const
{
	return TEXT("Matchmaking");
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetMatches::GetEndpointName() const
{
	return TEXT("GetMatches");
}

UClass* UK2BeamNode_ApiRequest_ApiMatchmakingGetMatches::GetApiClass() const
{
	return UBeamMatchmakingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiMatchmakingGetMatches::GetRequestClass() const
{
	return UApiMatchmakingGetMatchesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiMatchmakingGetMatches::GetResponseClass() const
{
	return UMatch::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetMatches::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiMatchmakingGetMatchesSuccess");
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetMatches::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiMatchmakingGetMatchesError");
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetMatches::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiMatchmakingGetMatchesComplete");
}

#undef LOCTEXT_NAMESPACE
