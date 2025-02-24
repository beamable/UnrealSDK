

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Matchmaking/K2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/ApiMatchmakingGetMatchesByIdRequest.h"
#include "BeamableCore/Public/AutoGen/Match.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetMatches);
}

FName UK2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiMatchmakingGetMatchesByIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById::GetServiceName() const
{
	return TEXT("Matchmaking");
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById::GetEndpointName() const
{
	return TEXT("GetMatches");
}

UClass* UK2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById::GetApiClass() const
{
	return UBeamMatchmakingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById::GetRequestClass() const
{
	return UApiMatchmakingGetMatchesByIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById::GetResponseClass() const
{
	return UMatch::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiMatchmakingGetMatchesByIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiMatchmakingGetMatchesByIdError");
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetMatchesById::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiMatchmakingGetMatchesByIdComplete");
}

#undef LOCTEXT_NAMESPACE
