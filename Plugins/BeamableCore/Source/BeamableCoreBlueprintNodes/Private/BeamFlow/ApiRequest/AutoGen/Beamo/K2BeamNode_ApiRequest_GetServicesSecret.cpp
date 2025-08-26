

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetServicesSecret.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetServicesSecretRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetServiceSecretResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetServicesSecret"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetServicesSecret::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetServicesSecret::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetServicesSecret);
}

FName UK2BeamNode_ApiRequest_GetServicesSecret::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetServicesSecretRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetServicesSecret::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetServicesSecret::GetEndpointName() const
{
	return TEXT("GetServicesSecret");
}

UClass* UK2BeamNode_ApiRequest_GetServicesSecret::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetServicesSecret::GetRequestClass() const
{
	return UGetServicesSecretRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetServicesSecret::GetResponseClass() const
{
	return UBeamoV2GetServiceSecretResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetServicesSecret::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetServicesSecretSuccess");
}

FString UK2BeamNode_ApiRequest_GetServicesSecret::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetServicesSecretError");
}

FString UK2BeamNode_ApiRequest_GetServicesSecret::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetServicesSecretComplete");
}

#undef LOCTEXT_NAMESPACE
