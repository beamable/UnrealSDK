

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostQueryLogsResult.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostQueryLogsResultRequest.h"
#include "BeamableCore/Public/AutoGen/GetSignedUrlResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostQueryLogsResult"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostQueryLogsResult::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostQueryLogsResult::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostQueryLogsResult);
}

FName UK2BeamNode_ApiRequest_PostQueryLogsResult::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostQueryLogsResultRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostQueryLogsResult::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostQueryLogsResult::GetEndpointName() const
{
	return TEXT("PostQueryLogsResult");
}

UClass* UK2BeamNode_ApiRequest_PostQueryLogsResult::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostQueryLogsResult::GetRequestClass() const
{
	return UPostQueryLogsResultRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostQueryLogsResult::GetResponseClass() const
{
	return UGetSignedUrlResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostQueryLogsResult::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostQueryLogsResultSuccess");
}

FString UK2BeamNode_ApiRequest_PostQueryLogsResult::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostQueryLogsResultError");
}

FString UK2BeamNode_ApiRequest_PostQueryLogsResult::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostQueryLogsResultComplete");
}

#undef LOCTEXT_NAMESPACE
