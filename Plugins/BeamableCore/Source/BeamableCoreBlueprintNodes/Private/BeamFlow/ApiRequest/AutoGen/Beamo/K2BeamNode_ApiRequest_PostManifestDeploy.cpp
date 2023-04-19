

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostManifestDeploy.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostManifestDeployRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostManifestDeploy"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostManifestDeploy::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostManifestDeploy::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostManifestDeploy);
}

FName UK2BeamNode_ApiRequest_PostManifestDeploy::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostManifestDeployRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostManifestDeploy::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostManifestDeploy::GetEndpointName() const
{
	return TEXT("PostManifestDeploy");
}

UClass* UK2BeamNode_ApiRequest_PostManifestDeploy::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestDeploy::GetRequestClass() const
{
	return UPostManifestDeployRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestDeploy::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostManifestDeploy::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostManifestDeploySuccess");
}

FString UK2BeamNode_ApiRequest_PostManifestDeploy::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostManifestDeployError");
}

FString UK2BeamNode_ApiRequest_PostManifestDeploy::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostManifestDeployComplete");
}

#undef LOCTEXT_NAMESPACE
