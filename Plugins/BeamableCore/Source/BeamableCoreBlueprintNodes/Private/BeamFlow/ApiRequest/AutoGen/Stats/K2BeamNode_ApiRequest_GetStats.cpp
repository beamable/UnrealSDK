

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_GetStats.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/GetStatsRequest.h"
#include "BeamableCore/Public/AutoGen/StatsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetStats"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetStats::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetStats::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetStats);
}

FName UK2BeamNode_ApiRequest_GetStats::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetStatsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetStats::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_GetStats::GetEndpointName() const
{
	return TEXT("GetStats");
}

UClass* UK2BeamNode_ApiRequest_GetStats::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetStats::GetRequestClass() const
{
	return UGetStatsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetStats::GetResponseClass() const
{
	return UStatsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetStats::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetStatsSuccess");
}

FString UK2BeamNode_ApiRequest_GetStats::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetStatsError");
}

FString UK2BeamNode_ApiRequest_GetStats::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetStatsComplete");
}

#undef LOCTEXT_NAMESPACE
