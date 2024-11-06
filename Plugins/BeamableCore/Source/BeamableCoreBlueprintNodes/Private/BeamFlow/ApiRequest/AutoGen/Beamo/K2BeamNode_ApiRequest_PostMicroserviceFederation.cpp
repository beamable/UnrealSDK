

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostMicroserviceFederation.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostMicroserviceFederationRequest.h"
#include "BeamableCore/Public/AutoGen/SupportedFederationsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostMicroserviceFederation"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostMicroserviceFederation::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostMicroserviceFederation::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostMicroserviceFederation);
}

FName UK2BeamNode_ApiRequest_PostMicroserviceFederation::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostMicroserviceFederationRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostMicroserviceFederation::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostMicroserviceFederation::GetEndpointName() const
{
	return TEXT("PostMicroserviceFederation");
}

UClass* UK2BeamNode_ApiRequest_PostMicroserviceFederation::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostMicroserviceFederation::GetRequestClass() const
{
	return UPostMicroserviceFederationRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostMicroserviceFederation::GetResponseClass() const
{
	return USupportedFederationsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostMicroserviceFederation::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostMicroserviceFederationSuccess");
}

FString UK2BeamNode_ApiRequest_PostMicroserviceFederation::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostMicroserviceFederationError");
}

FString UK2BeamNode_ApiRequest_PostMicroserviceFederation::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostMicroserviceFederationComplete");
}

#undef LOCTEXT_NAMESPACE
