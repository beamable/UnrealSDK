

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_BasicBeamoGetTemplates.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/BasicBeamoGetTemplatesRequest.h"
#include "BeamableCore/Public/AutoGen/GetTemplatesResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicBeamoGetTemplates"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicBeamoGetTemplates::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicBeamoGetTemplates::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, BasicBeamoGetTemplates);
}

FName UK2BeamNode_ApiRequest_BasicBeamoGetTemplates::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicBeamoGetTemplatesRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetTemplates::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetTemplates::GetEndpointName() const
{
	return TEXT("BasicBeamoGetTemplates");
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetTemplates::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetTemplates::GetRequestClass() const
{
	return UBasicBeamoGetTemplatesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetTemplates::GetResponseClass() const
{
	return UGetTemplatesResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetTemplates::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicBeamoGetTemplatesSuccess");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetTemplates::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicBeamoGetTemplatesError");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetTemplates::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicBeamoGetTemplatesComplete");
}

#undef LOCTEXT_NAMESPACE
