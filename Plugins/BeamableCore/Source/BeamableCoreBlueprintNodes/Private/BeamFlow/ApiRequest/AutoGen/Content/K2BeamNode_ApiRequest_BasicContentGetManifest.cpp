

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_BasicContentGetManifest.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/BasicContentGetManifestRequest.h"
#include "BeamableCore/Public/AutoGen/ContentBasicManifest.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicContentGetManifest"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicContentGetManifest::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicContentGetManifest::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetManifest);
}

FName UK2BeamNode_ApiRequest_BasicContentGetManifest::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicContentGetManifestRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicContentGetManifest::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_BasicContentGetManifest::GetEndpointName() const
{
	return TEXT("GetManifest");
}

UClass* UK2BeamNode_ApiRequest_BasicContentGetManifest::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicContentGetManifest::GetRequestClass() const
{
	return UBasicContentGetManifestRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicContentGetManifest::GetResponseClass() const
{
	return UContentBasicManifest::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicContentGetManifest::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicContentGetManifestSuccess");
}

FString UK2BeamNode_ApiRequest_BasicContentGetManifest::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicContentGetManifestError");
}

FString UK2BeamNode_ApiRequest_BasicContentGetManifest::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicContentGetManifestComplete");
}

#undef LOCTEXT_NAMESPACE
