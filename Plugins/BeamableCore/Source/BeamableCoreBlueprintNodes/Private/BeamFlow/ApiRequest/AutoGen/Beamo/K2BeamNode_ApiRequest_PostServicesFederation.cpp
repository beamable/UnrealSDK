

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostServicesFederation.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostServicesFederationRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2FederationRegistrationResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostServicesFederation"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostServicesFederation::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostServicesFederation::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostServicesFederation);
}

FName UK2BeamNode_ApiRequest_PostServicesFederation::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostServicesFederationRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostServicesFederation::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostServicesFederation::GetEndpointName() const
{
	return TEXT("PostServicesFederation");
}

UClass* UK2BeamNode_ApiRequest_PostServicesFederation::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostServicesFederation::GetRequestClass() const
{
	return UPostServicesFederationRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostServicesFederation::GetResponseClass() const
{
	return UBeamoV2FederationRegistrationResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostServicesFederation::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostServicesFederationSuccess");
}

FString UK2BeamNode_ApiRequest_PostServicesFederation::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostServicesFederationError");
}

FString UK2BeamNode_ApiRequest_PostServicesFederation::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostServicesFederationComplete");
}

#undef LOCTEXT_NAMESPACE
