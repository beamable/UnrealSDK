

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_ApiBeamoGetTemplates.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetTemplatesRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetTemplatesResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiBeamoGetTemplates"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiBeamoGetTemplates::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetTemplates::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, ApiBeamoGetTemplates);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetTemplates::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiBeamoGetTemplatesRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetTemplates::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetTemplates::GetEndpointName() const
{
	return TEXT("ApiBeamoGetTemplates");
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetTemplates::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetTemplates::GetRequestClass() const
{
	return UApiBeamoGetTemplatesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetTemplates::GetResponseClass() const
{
	return UBeamoV2GetTemplatesResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetTemplates::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiBeamoGetTemplatesSuccess");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetTemplates::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiBeamoGetTemplatesError");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetTemplates::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiBeamoGetTemplatesComplete");
}

#undef LOCTEXT_NAMESPACE
