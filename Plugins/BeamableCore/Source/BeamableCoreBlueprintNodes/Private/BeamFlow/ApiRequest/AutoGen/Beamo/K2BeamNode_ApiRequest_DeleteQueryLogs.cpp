

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_DeleteQueryLogs.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/DeleteQueryLogsRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteQueryLogs"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteQueryLogs::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteQueryLogs::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, DeleteQueryLogs);
}

FName UK2BeamNode_ApiRequest_DeleteQueryLogs::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteQueryLogsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteQueryLogs::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_DeleteQueryLogs::GetEndpointName() const
{
	return TEXT("DeleteQueryLogs");
}

UClass* UK2BeamNode_ApiRequest_DeleteQueryLogs::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteQueryLogs::GetRequestClass() const
{
	return UDeleteQueryLogsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteQueryLogs::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteQueryLogs::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteQueryLogsSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteQueryLogs::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteQueryLogsError");
}

FString UK2BeamNode_ApiRequest_DeleteQueryLogs::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteQueryLogsComplete");
}

#undef LOCTEXT_NAMESPACE
