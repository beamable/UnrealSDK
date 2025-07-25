

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostManifests.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostManifestsRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ManifestChecksum.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostManifests"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostManifests::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostManifests::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostManifests);
}

FName UK2BeamNode_ApiRequest_PostManifests::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostManifestsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostManifests::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostManifests::GetEndpointName() const
{
	return TEXT("PostManifests");
}

UClass* UK2BeamNode_ApiRequest_PostManifests::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifests::GetRequestClass() const
{
	return UPostManifestsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifests::GetResponseClass() const
{
	return UBeamoV2ManifestChecksum::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostManifests::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostManifestsSuccess");
}

FString UK2BeamNode_ApiRequest_PostManifests::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostManifestsError");
}

FString UK2BeamNode_ApiRequest_PostManifests::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostManifestsComplete");
}

#undef LOCTEXT_NAMESPACE
