

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetMicroserviceSecret.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetMicroserviceSecretRequest.h"
#include "BeamableCore/Public/AutoGen/MicroserviceSecretResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetMicroserviceSecret"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetMicroserviceSecret::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetMicroserviceSecret::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetMicroserviceSecret);
}

FName UK2BeamNode_ApiRequest_GetMicroserviceSecret::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetMicroserviceSecretRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetMicroserviceSecret::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetMicroserviceSecret::GetEndpointName() const
{
	return TEXT("GetMicroserviceSecret");
}

UClass* UK2BeamNode_ApiRequest_GetMicroserviceSecret::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMicroserviceSecret::GetRequestClass() const
{
	return UGetMicroserviceSecretRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMicroserviceSecret::GetResponseClass() const
{
	return UMicroserviceSecretResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetMicroserviceSecret::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetMicroserviceSecretSuccess");
}

FString UK2BeamNode_ApiRequest_GetMicroserviceSecret::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetMicroserviceSecretError");
}

FString UK2BeamNode_ApiRequest_GetMicroserviceSecret::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetMicroserviceSecretComplete");
}

#undef LOCTEXT_NAMESPACE
