

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Matchmaking/K2BeamNode_ApiRequest_DeleteMatch.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/DeleteMatchRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteMatch"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteMatch::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteMatch::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, DeleteMatch);
}

FName UK2BeamNode_ApiRequest_DeleteMatch::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteMatchRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteMatch::GetServiceName() const
{
	return TEXT("Matchmaking");
}

FString UK2BeamNode_ApiRequest_DeleteMatch::GetEndpointName() const
{
	return TEXT("DeleteMatch");
}

UClass* UK2BeamNode_ApiRequest_DeleteMatch::GetApiClass() const
{
	return UBeamMatchmakingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteMatch::GetRequestClass() const
{
	return UDeleteMatchRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteMatch::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteMatch::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteMatchSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteMatch::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteMatchError");
}

FString UK2BeamNode_ApiRequest_DeleteMatch::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteMatchComplete");
}

#undef LOCTEXT_NAMESPACE
