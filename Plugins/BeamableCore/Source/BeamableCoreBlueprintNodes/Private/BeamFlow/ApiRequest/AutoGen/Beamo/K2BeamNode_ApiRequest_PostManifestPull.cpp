

#include "BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostManifestPull.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamBeamoApi.h"
#include "AutoGen/SubSystems/Beamo/PostManifestPullRequest.h"
#include "AutoGen/ManifestChecksums.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostManifestPull"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostManifestPull::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostManifestPull::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostManifestPull);
}

FName UK2BeamNode_ApiRequest_PostManifestPull::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostManifestPullRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostManifestPull::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostManifestPull::GetEndpointName() const
{
	return TEXT("PostManifestPull");
}

UClass* UK2BeamNode_ApiRequest_PostManifestPull::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestPull::GetRequestClass() const
{
	return UPostManifestPullRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestPull::GetResponseClass() const
{
	return UManifestChecksums::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostManifestPull::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostManifestPullSuccess");
}

FString UK2BeamNode_ApiRequest_PostManifestPull::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostManifestPullError");
}

FString UK2BeamNode_ApiRequest_PostManifestPull::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostManifestPullComplete");
}

#undef LOCTEXT_NAMESPACE
