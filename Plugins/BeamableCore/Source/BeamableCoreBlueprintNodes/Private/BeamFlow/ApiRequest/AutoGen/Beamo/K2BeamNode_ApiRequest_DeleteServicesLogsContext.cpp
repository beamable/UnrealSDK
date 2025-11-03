

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_DeleteServicesLogsContext.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/DeleteServicesLogsContextRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteServicesLogsContext"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteServicesLogsContext::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteServicesLogsContext::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, DeleteServicesLogsContext);
}

FName UK2BeamNode_ApiRequest_DeleteServicesLogsContext::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteServicesLogsContextRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteServicesLogsContext::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_DeleteServicesLogsContext::GetEndpointName() const
{
	return TEXT("DeleteServicesLogsContext");
}

UClass* UK2BeamNode_ApiRequest_DeleteServicesLogsContext::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteServicesLogsContext::GetRequestClass() const
{
	return UDeleteServicesLogsContextRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteServicesLogsContext::GetResponseClass() const
{
	return UBeamoV2EmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteServicesLogsContext::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteServicesLogsContextSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteServicesLogsContext::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteServicesLogsContextError");
}

FString UK2BeamNode_ApiRequest_DeleteServicesLogsContext::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteServicesLogsContextComplete");
}

#undef LOCTEXT_NAMESPACE
