

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_BasicBeamoGetManifests.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/BasicBeamoGetManifestsRequest.h"
#include "BeamableCore/Public/AutoGen/GetManifestsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicBeamoGetManifests"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicBeamoGetManifests::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicBeamoGetManifests::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, BasicBeamoGetManifests);
}

FName UK2BeamNode_ApiRequest_BasicBeamoGetManifests::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicBeamoGetManifestsRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetManifests::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetManifests::GetEndpointName() const
{
	return TEXT("BasicBeamoGetManifests");
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetManifests::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetManifests::GetRequestClass() const
{
	return UBasicBeamoGetManifestsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetManifests::GetResponseClass() const
{
	return UGetManifestsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetManifests::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicBeamoGetManifestsSuccess");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetManifests::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicBeamoGetManifestsError");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetManifests::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicBeamoGetManifestsComplete");
}

#undef LOCTEXT_NAMESPACE
