

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_BasicContentPostManifestPull.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/BasicContentPostManifestPullRequest.h"
#include "BeamableCore/Public/AutoGen/ContentBasicManifest.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicContentPostManifestPull"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicContentPostManifestPull::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicContentPostManifestPull::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, PostManifestPull);
}

FName UK2BeamNode_ApiRequest_BasicContentPostManifestPull::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicContentPostManifestPullRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicContentPostManifestPull::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_BasicContentPostManifestPull::GetEndpointName() const
{
	return TEXT("PostManifestPull");
}

UClass* UK2BeamNode_ApiRequest_BasicContentPostManifestPull::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicContentPostManifestPull::GetRequestClass() const
{
	return UBasicContentPostManifestPullRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicContentPostManifestPull::GetResponseClass() const
{
	return UContentBasicManifest::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicContentPostManifestPull::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicContentPostManifestPullSuccess");
}

FString UK2BeamNode_ApiRequest_BasicContentPostManifestPull::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicContentPostManifestPullError");
}

FString UK2BeamNode_ApiRequest_BasicContentPostManifestPull::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicContentPostManifestPullComplete");
}

#undef LOCTEXT_NAMESPACE
