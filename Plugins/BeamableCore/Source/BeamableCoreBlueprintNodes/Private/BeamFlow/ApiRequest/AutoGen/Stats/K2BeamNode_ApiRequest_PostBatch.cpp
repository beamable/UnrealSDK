

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_PostBatch.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/PostBatchRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostBatch"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostBatch::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostBatch::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, PostBatch);
}

FName UK2BeamNode_ApiRequest_PostBatch::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostBatchRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostBatch::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_PostBatch::GetEndpointName() const
{
	return TEXT("PostBatch");
}

UClass* UK2BeamNode_ApiRequest_PostBatch::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostBatch::GetRequestClass() const
{
	return UPostBatchRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostBatch::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostBatch::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostBatchSuccess");
}

FString UK2BeamNode_ApiRequest_PostBatch::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostBatchError");
}

FString UK2BeamNode_ApiRequest_PostBatch::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostBatchComplete");
}

#undef LOCTEXT_NAMESPACE
