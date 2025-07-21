

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostServicesLogsQuery.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostServicesLogsQueryRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2QueryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostServicesLogsQuery"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostServicesLogsQuery::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostServicesLogsQuery::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostServicesLogsQuery);
}

FName UK2BeamNode_ApiRequest_PostServicesLogsQuery::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostServicesLogsQueryRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostServicesLogsQuery::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostServicesLogsQuery::GetEndpointName() const
{
	return TEXT("PostServicesLogsQuery");
}

UClass* UK2BeamNode_ApiRequest_PostServicesLogsQuery::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostServicesLogsQuery::GetRequestClass() const
{
	return UPostServicesLogsQueryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostServicesLogsQuery::GetResponseClass() const
{
	return UBeamoV2QueryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostServicesLogsQuery::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostServicesLogsQuerySuccess");
}

FString UK2BeamNode_ApiRequest_PostServicesLogsQuery::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostServicesLogsQueryError");
}

FString UK2BeamNode_ApiRequest_PostServicesLogsQuery::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostServicesLogsQueryComplete");
}

#undef LOCTEXT_NAMESPACE
