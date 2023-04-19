

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_DeleteStats.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/DeleteStatsRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteStats"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteStats::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteStats::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, DeleteStats);
}

FName UK2BeamNode_ApiRequest_DeleteStats::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteStatsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteStats::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_DeleteStats::GetEndpointName() const
{
	return TEXT("DeleteStats");
}

UClass* UK2BeamNode_ApiRequest_DeleteStats::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteStats::GetRequestClass() const
{
	return UDeleteStatsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteStats::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteStats::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteStatsSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteStats::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteStatsError");
}

FString UK2BeamNode_ApiRequest_DeleteStats::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteStatsComplete");
}

#undef LOCTEXT_NAMESPACE
