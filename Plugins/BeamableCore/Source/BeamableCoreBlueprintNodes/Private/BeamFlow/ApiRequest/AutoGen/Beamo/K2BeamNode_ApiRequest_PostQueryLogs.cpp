

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostQueryLogs.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostQueryLogsRequest.h"
#include "BeamableCore/Public/AutoGen/Query.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostQueryLogs"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostQueryLogs::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostQueryLogs::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostQueryLogs);
}

FName UK2BeamNode_ApiRequest_PostQueryLogs::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostQueryLogsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostQueryLogs::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostQueryLogs::GetEndpointName() const
{
	return TEXT("PostQueryLogs");
}

UClass* UK2BeamNode_ApiRequest_PostQueryLogs::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostQueryLogs::GetRequestClass() const
{
	return UPostQueryLogsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostQueryLogs::GetResponseClass() const
{
	return UQuery::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostQueryLogs::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostQueryLogsSuccess");
}

FString UK2BeamNode_ApiRequest_PostQueryLogs::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostQueryLogsError");
}

FString UK2BeamNode_ApiRequest_PostQueryLogs::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostQueryLogsComplete");
}

#undef LOCTEXT_NAMESPACE
