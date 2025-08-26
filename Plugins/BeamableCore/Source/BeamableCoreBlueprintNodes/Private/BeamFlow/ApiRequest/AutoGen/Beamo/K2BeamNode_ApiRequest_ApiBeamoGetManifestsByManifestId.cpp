

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetManifestsByManifestIdRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2Manifest.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, ApiBeamoGetManifestsByManifestId);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiBeamoGetManifestsByManifestIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId::GetEndpointName() const
{
	return TEXT("ApiBeamoGetManifestsByManifestId");
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId::GetRequestClass() const
{
	return UApiBeamoGetManifestsByManifestIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId::GetResponseClass() const
{
	return UBeamoV2Manifest::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiBeamoGetManifestsByManifestIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiBeamoGetManifestsByManifestIdError");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetManifestsByManifestId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiBeamoGetManifestsByManifestIdComplete");
}

#undef LOCTEXT_NAMESPACE
