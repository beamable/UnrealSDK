

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetServicesLogsQuery.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetServicesLogsQueryRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2SignedRequestBody.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetServicesLogsQuery"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetServicesLogsQuery::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetServicesLogsQuery::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetServicesLogsQuery);
}

FName UK2BeamNode_ApiRequest_GetServicesLogsQuery::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetServicesLogsQueryRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetServicesLogsQuery::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetServicesLogsQuery::GetEndpointName() const
{
	return TEXT("GetServicesLogsQuery");
}

UClass* UK2BeamNode_ApiRequest_GetServicesLogsQuery::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetServicesLogsQuery::GetRequestClass() const
{
	return UGetServicesLogsQueryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetServicesLogsQuery::GetResponseClass() const
{
	return UBeamoV2SignedRequestBody::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetServicesLogsQuery::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetServicesLogsQuerySuccess");
}

FString UK2BeamNode_ApiRequest_GetServicesLogsQuery::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetServicesLogsQueryError");
}

FString UK2BeamNode_ApiRequest_GetServicesLogsQuery::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetServicesLogsQueryComplete");
}

#undef LOCTEXT_NAMESPACE
