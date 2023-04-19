

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_BasicBeamoPostManifestPull.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/BasicBeamoPostManifestPullRequest.h"
#include "BeamableCore/Public/AutoGen/ManifestChecksums.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicBeamoPostManifestPull"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicBeamoPostManifestPull::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicBeamoPostManifestPull::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostManifestPull);
}

FName UK2BeamNode_ApiRequest_BasicBeamoPostManifestPull::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicBeamoPostManifestPullRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicBeamoPostManifestPull::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_BasicBeamoPostManifestPull::GetEndpointName() const
{
	return TEXT("PostManifestPull");
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoPostManifestPull::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoPostManifestPull::GetRequestClass() const
{
	return UBasicBeamoPostManifestPullRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoPostManifestPull::GetResponseClass() const
{
	return UManifestChecksums::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicBeamoPostManifestPull::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicBeamoPostManifestPullSuccess");
}

FString UK2BeamNode_ApiRequest_BasicBeamoPostManifestPull::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicBeamoPostManifestPullError");
}

FString UK2BeamNode_ApiRequest_BasicBeamoPostManifestPull::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicBeamoPostManifestPullComplete");
}

#undef LOCTEXT_NAMESPACE
