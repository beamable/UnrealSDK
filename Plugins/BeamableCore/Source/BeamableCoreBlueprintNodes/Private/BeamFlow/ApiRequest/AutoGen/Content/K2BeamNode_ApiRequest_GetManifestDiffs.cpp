

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_GetManifestDiffs.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestDiffsRequest.h"
#include "BeamableCore/Public/AutoGen/GetManifestDiffsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifestDiffs"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifestDiffs::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifestDiffs::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetManifestDiffs);
}

FName UK2BeamNode_ApiRequest_GetManifestDiffs::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestDiffsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifestDiffs::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_GetManifestDiffs::GetEndpointName() const
{
	return TEXT("GetManifestDiffs");
}

UClass* UK2BeamNode_ApiRequest_GetManifestDiffs::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestDiffs::GetRequestClass() const
{
	return UGetManifestDiffsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestDiffs::GetResponseClass() const
{
	return UGetManifestDiffsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifestDiffs::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestDiffsSuccess");
}

FString UK2BeamNode_ApiRequest_GetManifestDiffs::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestDiffsError");
}

FString UK2BeamNode_ApiRequest_GetManifestDiffs::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestDiffsComplete");
}

#undef LOCTEXT_NAMESPACE
