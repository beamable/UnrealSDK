

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetServicesLogsContextByServiceNameRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceLoggingContext.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, ApiBeamoGetServicesLogsContextByServiceName);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiBeamoGetServicesLogsContextByServiceNameRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName::GetEndpointName() const
{
	return TEXT("ApiBeamoGetServicesLogsContextByServiceName");
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName::GetRequestClass() const
{
	return UApiBeamoGetServicesLogsContextByServiceNameRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName::GetResponseClass() const
{
	return UBeamoV2ServiceLoggingContext::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiBeamoGetServicesLogsContextByServiceNameSuccess");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiBeamoGetServicesLogsContextByServiceNameError");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContextByServiceName::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiBeamoGetServicesLogsContextByServiceNameComplete");
}

#undef LOCTEXT_NAMESPACE
