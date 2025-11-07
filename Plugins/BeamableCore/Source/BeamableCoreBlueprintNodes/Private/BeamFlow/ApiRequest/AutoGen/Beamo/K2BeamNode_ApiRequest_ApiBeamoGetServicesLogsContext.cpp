

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetServicesLogsContextRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetAllServiceLoggingContexts.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, ApiBeamoGetServicesLogsContext);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiBeamoGetServicesLogsContextRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext::GetEndpointName() const
{
	return TEXT("ApiBeamoGetServicesLogsContext");
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext::GetRequestClass() const
{
	return UApiBeamoGetServicesLogsContextRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext::GetResponseClass() const
{
	return UBeamoV2GetAllServiceLoggingContexts::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiBeamoGetServicesLogsContextSuccess");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiBeamoGetServicesLogsContextError");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetServicesLogsContext::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiBeamoGetServicesLogsContextComplete");
}

#undef LOCTEXT_NAMESPACE
