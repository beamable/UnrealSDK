

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostServicesRegistrations.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostServicesRegistrationsRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceRegistrationResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostServicesRegistrations"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostServicesRegistrations::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostServicesRegistrations::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostServicesRegistrations);
}

FName UK2BeamNode_ApiRequest_PostServicesRegistrations::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostServicesRegistrationsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostServicesRegistrations::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostServicesRegistrations::GetEndpointName() const
{
	return TEXT("PostServicesRegistrations");
}

UClass* UK2BeamNode_ApiRequest_PostServicesRegistrations::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostServicesRegistrations::GetRequestClass() const
{
	return UPostServicesRegistrationsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostServicesRegistrations::GetResponseClass() const
{
	return UBeamoV2ServiceRegistrationResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostServicesRegistrations::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostServicesRegistrationsSuccess");
}

FString UK2BeamNode_ApiRequest_PostServicesRegistrations::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostServicesRegistrationsError");
}

FString UK2BeamNode_ApiRequest_PostServicesRegistrations::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostServicesRegistrationsComplete");
}

#undef LOCTEXT_NAMESPACE
