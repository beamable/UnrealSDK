

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostMetricsUrl.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostMetricsUrlRequest.h"
#include "BeamableCore/Public/AutoGen/GetSignedUrlResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostMetricsUrl"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostMetricsUrl::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostMetricsUrl::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostMetricsUrl);
}

FName UK2BeamNode_ApiRequest_PostMetricsUrl::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostMetricsUrlRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostMetricsUrl::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostMetricsUrl::GetEndpointName() const
{
	return TEXT("PostMetricsUrl");
}

UClass* UK2BeamNode_ApiRequest_PostMetricsUrl::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostMetricsUrl::GetRequestClass() const
{
	return UPostMetricsUrlRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostMetricsUrl::GetResponseClass() const
{
	return UGetSignedUrlResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostMetricsUrl::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostMetricsUrlSuccess");
}

FString UK2BeamNode_ApiRequest_PostMetricsUrl::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostMetricsUrlError");
}

FString UK2BeamNode_ApiRequest_PostMetricsUrl::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostMetricsUrlComplete");
}

#undef LOCTEXT_NAMESPACE
