

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/BeamoOtel/K2BeamNode_ApiRequest_GetOtelAuthWriterConfig.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoOtelApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/BeamoOtel/GetOtelAuthWriterConfigRequest.h"
#include "BeamableCore/Public/AutoGen/OtelAuthConfig.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetOtelAuthWriterConfig"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetOtelAuthWriterConfig::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoOtelApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetOtelAuthWriterConfig::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoOtelApi, GetOtelAuthWriterConfig);
}

FName UK2BeamNode_ApiRequest_GetOtelAuthWriterConfig::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetOtelAuthWriterConfigRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetOtelAuthWriterConfig::GetServiceName() const
{
	return TEXT("BeamoOtel");
}

FString UK2BeamNode_ApiRequest_GetOtelAuthWriterConfig::GetEndpointName() const
{
	return TEXT("GetOtelAuthWriterConfig");
}

UClass* UK2BeamNode_ApiRequest_GetOtelAuthWriterConfig::GetApiClass() const
{
	return UBeamBeamoOtelApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetOtelAuthWriterConfig::GetRequestClass() const
{
	return UGetOtelAuthWriterConfigRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetOtelAuthWriterConfig::GetResponseClass() const
{
	return UOtelAuthConfig::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetOtelAuthWriterConfig::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetOtelAuthWriterConfigSuccess");
}

FString UK2BeamNode_ApiRequest_GetOtelAuthWriterConfig::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetOtelAuthWriterConfigError");
}

FString UK2BeamNode_ApiRequest_GetOtelAuthWriterConfig::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetOtelAuthWriterConfigComplete");
}

#undef LOCTEXT_NAMESPACE
