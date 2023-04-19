

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_PostManifestsPull.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostManifestsPullRequest.h"
#include "BeamableCore/Public/AutoGen/ManifestChecksums.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostManifestsPull"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostManifestsPull::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostManifestsPull::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, PostManifestsPull);
}

FName UK2BeamNode_ApiRequest_PostManifestsPull::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostManifestsPullRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostManifestsPull::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_PostManifestsPull::GetEndpointName() const
{
	return TEXT("PostManifestsPull");
}

UClass* UK2BeamNode_ApiRequest_PostManifestsPull::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestsPull::GetRequestClass() const
{
	return UPostManifestsPullRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestsPull::GetResponseClass() const
{
	return UManifestChecksums::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostManifestsPull::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostManifestsPullSuccess");
}

FString UK2BeamNode_ApiRequest_PostManifestsPull::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostManifestsPullError");
}

FString UK2BeamNode_ApiRequest_PostManifestsPull::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostManifestsPullComplete");
}

#undef LOCTEXT_NAMESPACE
