

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/BeamoOtel/K2BeamNode_ApiRequest_GetOtelAuthReaderConfig.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoOtelApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/BeamoOtel/GetOtelAuthReaderConfigRequest.h"
#include "BeamableCore/Public/AutoGen/OtelAuthConfig.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetOtelAuthReaderConfig"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetOtelAuthReaderConfig::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoOtelApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetOtelAuthReaderConfig::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoOtelApi, GetOtelAuthReaderConfig);
}

FName UK2BeamNode_ApiRequest_GetOtelAuthReaderConfig::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetOtelAuthReaderConfigRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetOtelAuthReaderConfig::GetServiceName() const
{
	return TEXT("BeamoOtel");
}

FString UK2BeamNode_ApiRequest_GetOtelAuthReaderConfig::GetEndpointName() const
{
	return TEXT("GetOtelAuthReaderConfig");
}

UClass* UK2BeamNode_ApiRequest_GetOtelAuthReaderConfig::GetApiClass() const
{
	return UBeamBeamoOtelApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetOtelAuthReaderConfig::GetRequestClass() const
{
	return UGetOtelAuthReaderConfigRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetOtelAuthReaderConfig::GetResponseClass() const
{
	return UOtelAuthConfig::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetOtelAuthReaderConfig::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetOtelAuthReaderConfigSuccess");
}

FString UK2BeamNode_ApiRequest_GetOtelAuthReaderConfig::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetOtelAuthReaderConfigError");
}

FString UK2BeamNode_ApiRequest_GetOtelAuthReaderConfig::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetOtelAuthReaderConfigComplete");
}

#undef LOCTEXT_NAMESPACE
