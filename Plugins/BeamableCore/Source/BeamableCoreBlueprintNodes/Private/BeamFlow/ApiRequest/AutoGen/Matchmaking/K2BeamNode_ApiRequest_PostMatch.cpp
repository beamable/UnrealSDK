

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Matchmaking/K2BeamNode_ApiRequest_PostMatch.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/PostMatchRequest.h"
#include "BeamableCore/Public/AutoGen/MatchUpdate.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostMatch"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostMatch::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostMatch::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, PostMatch);
}

FName UK2BeamNode_ApiRequest_PostMatch::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostMatchRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostMatch::GetServiceName() const
{
	return TEXT("Matchmaking");
}

FString UK2BeamNode_ApiRequest_PostMatch::GetEndpointName() const
{
	return TEXT("PostMatch");
}

UClass* UK2BeamNode_ApiRequest_PostMatch::GetApiClass() const
{
	return UBeamMatchmakingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostMatch::GetRequestClass() const
{
	return UPostMatchRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostMatch::GetResponseClass() const
{
	return UMatchUpdate::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostMatch::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostMatchSuccess");
}

FString UK2BeamNode_ApiRequest_PostMatch::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostMatchError");
}

FString UK2BeamNode_ApiRequest_PostMatch::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostMatchComplete");
}

#undef LOCTEXT_NAMESPACE
