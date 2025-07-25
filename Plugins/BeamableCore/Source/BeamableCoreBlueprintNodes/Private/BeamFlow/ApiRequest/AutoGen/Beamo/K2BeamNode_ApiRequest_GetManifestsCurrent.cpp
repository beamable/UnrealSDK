

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetManifestsCurrent.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetManifestsCurrentRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2Manifest.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifestsCurrent"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifestsCurrent::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifestsCurrent::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetManifestsCurrent);
}

FName UK2BeamNode_ApiRequest_GetManifestsCurrent::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestsCurrentRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifestsCurrent::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetManifestsCurrent::GetEndpointName() const
{
	return TEXT("GetManifestsCurrent");
}

UClass* UK2BeamNode_ApiRequest_GetManifestsCurrent::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestsCurrent::GetRequestClass() const
{
	return UGetManifestsCurrentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestsCurrent::GetResponseClass() const
{
	return UBeamoV2Manifest::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifestsCurrent::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestsCurrentSuccess");
}

FString UK2BeamNode_ApiRequest_GetManifestsCurrent::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestsCurrentError");
}

FString UK2BeamNode_ApiRequest_GetManifestsCurrent::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestsCurrentComplete");
}

#undef LOCTEXT_NAMESPACE
