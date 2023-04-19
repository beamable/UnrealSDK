

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_GetClientBatch.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/GetClientBatchRequest.h"
#include "BeamableCore/Public/AutoGen/BatchReadStatsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetClientBatch"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetClientBatch::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetClientBatch::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetClientBatch);
}

FName UK2BeamNode_ApiRequest_GetClientBatch::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetClientBatchRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetClientBatch::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_GetClientBatch::GetEndpointName() const
{
	return TEXT("GetClientBatch");
}

UClass* UK2BeamNode_ApiRequest_GetClientBatch::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetClientBatch::GetRequestClass() const
{
	return UGetClientBatchRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetClientBatch::GetResponseClass() const
{
	return UBatchReadStatsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetClientBatch::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetClientBatchSuccess");
}

FString UK2BeamNode_ApiRequest_GetClientBatch::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetClientBatchError");
}

FString UK2BeamNode_ApiRequest_GetClientBatch::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetClientBatchComplete");
}

#undef LOCTEXT_NAMESPACE
