

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_BasicStatsPostSearch.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/BasicStatsPostSearchRequest.h"
#include "BeamableCore/Public/AutoGen/StatsSearchResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicStatsPostSearch"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicStatsPostSearch::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicStatsPostSearch::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, PostSearch);
}

FName UK2BeamNode_ApiRequest_BasicStatsPostSearch::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicStatsPostSearchRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicStatsPostSearch::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_BasicStatsPostSearch::GetEndpointName() const
{
	return TEXT("PostSearch");
}

UClass* UK2BeamNode_ApiRequest_BasicStatsPostSearch::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicStatsPostSearch::GetRequestClass() const
{
	return UBasicStatsPostSearchRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicStatsPostSearch::GetResponseClass() const
{
	return UStatsSearchResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicStatsPostSearch::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicStatsPostSearchSuccess");
}

FString UK2BeamNode_ApiRequest_BasicStatsPostSearch::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicStatsPostSearchError");
}

FString UK2BeamNode_ApiRequest_BasicStatsPostSearch::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicStatsPostSearchComplete");
}

#undef LOCTEXT_NAMESPACE
