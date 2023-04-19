

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_PostStats.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/PostStatsRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostStats"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostStats::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostStats::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, PostStats);
}

FName UK2BeamNode_ApiRequest_PostStats::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostStatsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostStats::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_PostStats::GetEndpointName() const
{
	return TEXT("PostStats");
}

UClass* UK2BeamNode_ApiRequest_PostStats::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostStats::GetRequestClass() const
{
	return UPostStatsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostStats::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostStats::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostStatsSuccess");
}

FString UK2BeamNode_ApiRequest_PostStats::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostStatsError");
}

FString UK2BeamNode_ApiRequest_PostStats::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostStatsComplete");
}

#undef LOCTEXT_NAMESPACE
