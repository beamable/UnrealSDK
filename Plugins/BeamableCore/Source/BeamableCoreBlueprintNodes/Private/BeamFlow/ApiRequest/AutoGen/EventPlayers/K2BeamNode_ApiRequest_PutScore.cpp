

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/EventPlayers/K2BeamNode_ApiRequest_PutScore.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventPlayersApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/EventPlayers/PutScoreRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutScore"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutScore::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventPlayersApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutScore::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventPlayersApi, PutScore);
}

FName UK2BeamNode_ApiRequest_PutScore::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutScoreRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutScore::GetServiceName() const
{
	return TEXT("EventPlayers");
}

FString UK2BeamNode_ApiRequest_PutScore::GetEndpointName() const
{
	return TEXT("PutScore");
}

UClass* UK2BeamNode_ApiRequest_PutScore::GetApiClass() const
{
	return UBeamEventPlayersApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutScore::GetRequestClass() const
{
	return UPutScoreRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutScore::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutScore::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutScoreSuccess");
}

FString UK2BeamNode_ApiRequest_PutScore::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutScoreError");
}

FString UK2BeamNode_ApiRequest_PutScore::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutScoreComplete");
}

#undef LOCTEXT_NAMESPACE
