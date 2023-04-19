

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_BasicBeamoPostManifest.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/BasicBeamoPostManifestRequest.h"
#include "BeamableCore/Public/AutoGen/PostManifestResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicBeamoPostManifest"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicBeamoPostManifest::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicBeamoPostManifest::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostManifest);
}

FName UK2BeamNode_ApiRequest_BasicBeamoPostManifest::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicBeamoPostManifestRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicBeamoPostManifest::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_BasicBeamoPostManifest::GetEndpointName() const
{
	return TEXT("PostManifest");
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoPostManifest::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoPostManifest::GetRequestClass() const
{
	return UBasicBeamoPostManifestRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoPostManifest::GetResponseClass() const
{
	return UPostManifestResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicBeamoPostManifest::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicBeamoPostManifestSuccess");
}

FString UK2BeamNode_ApiRequest_BasicBeamoPostManifest::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicBeamoPostManifestError");
}

FString UK2BeamNode_ApiRequest_BasicBeamoPostManifest::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicBeamoPostManifestComplete");
}

#undef LOCTEXT_NAMESPACE
