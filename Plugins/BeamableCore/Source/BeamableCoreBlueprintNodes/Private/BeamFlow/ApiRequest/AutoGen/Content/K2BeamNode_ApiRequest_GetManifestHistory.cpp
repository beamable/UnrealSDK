

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_GetManifestHistory.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestHistoryRequest.h"
#include "BeamableCore/Public/AutoGen/GetManifestHistoryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifestHistory"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifestHistory::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifestHistory::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetManifestHistory);
}

FName UK2BeamNode_ApiRequest_GetManifestHistory::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestHistoryRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifestHistory::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_GetManifestHistory::GetEndpointName() const
{
	return TEXT("GetManifestHistory");
}

UClass* UK2BeamNode_ApiRequest_GetManifestHistory::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestHistory::GetRequestClass() const
{
	return UGetManifestHistoryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestHistory::GetResponseClass() const
{
	return UGetManifestHistoryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifestHistory::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestHistorySuccess");
}

FString UK2BeamNode_ApiRequest_GetManifestHistory::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestHistoryError");
}

FString UK2BeamNode_ApiRequest_GetManifestHistory::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestHistoryComplete");
}

#undef LOCTEXT_NAMESPACE
