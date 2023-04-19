

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetTemplates.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetTemplatesRequest.h"
#include "BeamableCore/Public/AutoGen/GetTemplatesResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetTemplates"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetTemplates::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetTemplates::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetTemplates);
}

FName UK2BeamNode_ApiRequest_GetTemplates::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetTemplatesRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetTemplates::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetTemplates::GetEndpointName() const
{
	return TEXT("GetTemplates");
}

UClass* UK2BeamNode_ApiRequest_GetTemplates::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetTemplates::GetRequestClass() const
{
	return UGetTemplatesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetTemplates::GetResponseClass() const
{
	return UGetTemplatesResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetTemplates::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetTemplatesSuccess");
}

FString UK2BeamNode_ApiRequest_GetTemplates::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetTemplatesError");
}

FString UK2BeamNode_ApiRequest_GetTemplates::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetTemplatesComplete");
}

#undef LOCTEXT_NAMESPACE
