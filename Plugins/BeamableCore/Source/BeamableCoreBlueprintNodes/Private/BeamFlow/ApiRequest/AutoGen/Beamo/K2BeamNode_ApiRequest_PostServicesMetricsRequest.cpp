

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostServicesMetricsRequest.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostServicesMetricsRequestRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2SignedRequestBody.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostServicesMetricsRequest"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostServicesMetricsRequest::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostServicesMetricsRequest::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostServicesMetricsRequest);
}

FName UK2BeamNode_ApiRequest_PostServicesMetricsRequest::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostServicesMetricsRequestRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostServicesMetricsRequest::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostServicesMetricsRequest::GetEndpointName() const
{
	return TEXT("PostServicesMetricsRequest");
}

UClass* UK2BeamNode_ApiRequest_PostServicesMetricsRequest::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostServicesMetricsRequest::GetRequestClass() const
{
	return UPostServicesMetricsRequestRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostServicesMetricsRequest::GetResponseClass() const
{
	return UBeamoV2SignedRequestBody::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostServicesMetricsRequest::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostServicesMetricsRequestSuccess");
}

FString UK2BeamNode_ApiRequest_PostServicesMetricsRequest::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostServicesMetricsRequestError");
}

FString UK2BeamNode_ApiRequest_PostServicesMetricsRequest::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostServicesMetricsRequestComplete");
}

#undef LOCTEXT_NAMESPACE
