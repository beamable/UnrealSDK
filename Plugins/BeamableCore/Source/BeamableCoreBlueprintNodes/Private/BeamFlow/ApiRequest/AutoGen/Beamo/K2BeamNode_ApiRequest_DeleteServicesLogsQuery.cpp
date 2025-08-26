

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_DeleteServicesLogsQuery.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/DeleteServicesLogsQueryRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteServicesLogsQuery"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteServicesLogsQuery::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteServicesLogsQuery::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, DeleteServicesLogsQuery);
}

FName UK2BeamNode_ApiRequest_DeleteServicesLogsQuery::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteServicesLogsQueryRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteServicesLogsQuery::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_DeleteServicesLogsQuery::GetEndpointName() const
{
	return TEXT("DeleteServicesLogsQuery");
}

UClass* UK2BeamNode_ApiRequest_DeleteServicesLogsQuery::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteServicesLogsQuery::GetRequestClass() const
{
	return UDeleteServicesLogsQueryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteServicesLogsQuery::GetResponseClass() const
{
	return UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteServicesLogsQuery::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteServicesLogsQuerySuccess");
}

FString UK2BeamNode_ApiRequest_DeleteServicesLogsQuery::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteServicesLogsQueryError");
}

FString UK2BeamNode_ApiRequest_DeleteServicesLogsQuery::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteServicesLogsQueryComplete");
}

#undef LOCTEXT_NAMESPACE
