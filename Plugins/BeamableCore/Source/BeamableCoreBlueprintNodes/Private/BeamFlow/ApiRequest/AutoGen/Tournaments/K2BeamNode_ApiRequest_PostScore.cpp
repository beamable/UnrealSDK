

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_PostScore.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/PostScoreRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostScore"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostScore::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostScore::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, PostScore);
}

FName UK2BeamNode_ApiRequest_PostScore::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostScoreRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostScore::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_PostScore::GetEndpointName() const
{
	return TEXT("PostScore");
}

UClass* UK2BeamNode_ApiRequest_PostScore::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostScore::GetRequestClass() const
{
	return UPostScoreRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostScore::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostScore::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostScoreSuccess");
}

FString UK2BeamNode_ApiRequest_PostScore::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostScoreError");
}

FString UK2BeamNode_ApiRequest_PostScore::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostScoreComplete");
}

#undef LOCTEXT_NAMESPACE
