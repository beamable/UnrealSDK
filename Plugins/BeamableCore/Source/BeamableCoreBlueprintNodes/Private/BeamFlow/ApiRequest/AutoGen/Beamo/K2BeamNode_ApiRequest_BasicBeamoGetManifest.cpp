

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_BasicBeamoGetManifest.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/BasicBeamoGetManifestRequest.h"
#include "BeamableCore/Public/AutoGen/GetManifestResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicBeamoGetManifest"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicBeamoGetManifest::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicBeamoGetManifest::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetManifest);
}

FName UK2BeamNode_ApiRequest_BasicBeamoGetManifest::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicBeamoGetManifestRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetManifest::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetManifest::GetEndpointName() const
{
	return TEXT("GetManifest");
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetManifest::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetManifest::GetRequestClass() const
{
	return UBasicBeamoGetManifestRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetManifest::GetResponseClass() const
{
	return UGetManifestResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetManifest::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicBeamoGetManifestSuccess");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetManifest::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicBeamoGetManifestError");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetManifest::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicBeamoGetManifestComplete");
}

#undef LOCTEXT_NAMESPACE
