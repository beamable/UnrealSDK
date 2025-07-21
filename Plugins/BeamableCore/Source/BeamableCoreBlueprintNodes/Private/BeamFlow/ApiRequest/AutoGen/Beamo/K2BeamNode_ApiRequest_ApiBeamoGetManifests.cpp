

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_ApiBeamoGetManifests.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetManifestsRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetManifestsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiBeamoGetManifests"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiBeamoGetManifests::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetManifests::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, ApiBeamoGetManifests);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetManifests::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiBeamoGetManifestsRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetManifests::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetManifests::GetEndpointName() const
{
	return TEXT("ApiBeamoGetManifests");
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetManifests::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetManifests::GetRequestClass() const
{
	return UApiBeamoGetManifestsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetManifests::GetResponseClass() const
{
	return UBeamoV2GetManifestsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetManifests::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiBeamoGetManifestsSuccess");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetManifests::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiBeamoGetManifestsError");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetManifests::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiBeamoGetManifestsComplete");
}

#undef LOCTEXT_NAMESPACE
