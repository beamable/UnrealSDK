

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_BasicContentPostManifest.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/BasicContentPostManifestRequest.h"
#include "BeamableCore/Public/AutoGen/ContentBasicManifest.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicContentPostManifest"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicContentPostManifest::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicContentPostManifest::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, PostManifest);
}

FName UK2BeamNode_ApiRequest_BasicContentPostManifest::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicContentPostManifestRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicContentPostManifest::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_BasicContentPostManifest::GetEndpointName() const
{
	return TEXT("PostManifest");
}

UClass* UK2BeamNode_ApiRequest_BasicContentPostManifest::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicContentPostManifest::GetRequestClass() const
{
	return UBasicContentPostManifestRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicContentPostManifest::GetResponseClass() const
{
	return UContentBasicManifest::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicContentPostManifest::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicContentPostManifestSuccess");
}

FString UK2BeamNode_ApiRequest_BasicContentPostManifest::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicContentPostManifestError");
}

FString UK2BeamNode_ApiRequest_BasicContentPostManifest::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicContentPostManifestComplete");
}

#undef LOCTEXT_NAMESPACE
