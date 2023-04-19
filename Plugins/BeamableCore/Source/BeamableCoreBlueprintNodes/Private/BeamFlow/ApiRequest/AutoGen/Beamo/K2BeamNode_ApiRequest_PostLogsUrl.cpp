

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostLogsUrl.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostLogsUrlRequest.h"
#include "BeamableCore/Public/AutoGen/GetSignedUrlResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostLogsUrl"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostLogsUrl::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostLogsUrl::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostLogsUrl);
}

FName UK2BeamNode_ApiRequest_PostLogsUrl::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostLogsUrlRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostLogsUrl::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostLogsUrl::GetEndpointName() const
{
	return TEXT("PostLogsUrl");
}

UClass* UK2BeamNode_ApiRequest_PostLogsUrl::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostLogsUrl::GetRequestClass() const
{
	return UPostLogsUrlRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostLogsUrl::GetResponseClass() const
{
	return UGetSignedUrlResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostLogsUrl::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostLogsUrlSuccess");
}

FString UK2BeamNode_ApiRequest_PostLogsUrl::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostLogsUrlError");
}

FString UK2BeamNode_ApiRequest_PostLogsUrl::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostLogsUrlComplete");
}

#undef LOCTEXT_NAMESPACE
