

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostMicroserviceRegistrations.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostMicroserviceRegistrationsRequest.h"
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostMicroserviceRegistrations"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostMicroserviceRegistrations::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostMicroserviceRegistrations::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostMicroserviceRegistrations);
}

FName UK2BeamNode_ApiRequest_PostMicroserviceRegistrations::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostMicroserviceRegistrationsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostMicroserviceRegistrations::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostMicroserviceRegistrations::GetEndpointName() const
{
	return TEXT("PostMicroserviceRegistrations");
}

UClass* UK2BeamNode_ApiRequest_PostMicroserviceRegistrations::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostMicroserviceRegistrations::GetRequestClass() const
{
	return UPostMicroserviceRegistrationsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostMicroserviceRegistrations::GetResponseClass() const
{
	return UMicroserviceRegistrationsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostMicroserviceRegistrations::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostMicroserviceRegistrationsSuccess");
}

FString UK2BeamNode_ApiRequest_PostMicroserviceRegistrations::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostMicroserviceRegistrationsError");
}

FString UK2BeamNode_ApiRequest_PostMicroserviceRegistrations::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostMicroserviceRegistrationsComplete");
}

#undef LOCTEXT_NAMESPACE
