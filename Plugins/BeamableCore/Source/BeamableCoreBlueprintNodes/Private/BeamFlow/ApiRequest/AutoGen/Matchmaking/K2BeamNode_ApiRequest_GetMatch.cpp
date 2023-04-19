

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Matchmaking/K2BeamNode_ApiRequest_GetMatch.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/GetMatchRequest.h"
#include "BeamableCore/Public/AutoGen/MatchUpdate.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetMatch"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetMatch::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetMatch::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetMatch);
}

FName UK2BeamNode_ApiRequest_GetMatch::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetMatchRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetMatch::GetServiceName() const
{
	return TEXT("Matchmaking");
}

FString UK2BeamNode_ApiRequest_GetMatch::GetEndpointName() const
{
	return TEXT("GetMatch");
}

UClass* UK2BeamNode_ApiRequest_GetMatch::GetApiClass() const
{
	return UBeamMatchmakingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMatch::GetRequestClass() const
{
	return UGetMatchRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMatch::GetResponseClass() const
{
	return UMatchUpdate::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetMatch::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetMatchSuccess");
}

FString UK2BeamNode_ApiRequest_GetMatch::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetMatchError");
}

FString UK2BeamNode_ApiRequest_GetMatch::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetMatchComplete");
}

#undef LOCTEXT_NAMESPACE
