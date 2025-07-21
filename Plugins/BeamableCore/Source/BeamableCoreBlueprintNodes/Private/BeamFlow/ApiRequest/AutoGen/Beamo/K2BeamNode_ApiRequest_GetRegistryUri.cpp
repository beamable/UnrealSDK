

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetRegistryUri.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetRegistryUriRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2UriResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRegistryUri"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRegistryUri::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRegistryUri::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetRegistryUri);
}

FName UK2BeamNode_ApiRequest_GetRegistryUri::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRegistryUriRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRegistryUri::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetRegistryUri::GetEndpointName() const
{
	return TEXT("GetRegistryUri");
}

UClass* UK2BeamNode_ApiRequest_GetRegistryUri::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRegistryUri::GetRequestClass() const
{
	return UGetRegistryUriRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRegistryUri::GetResponseClass() const
{
	return UBeamoV2UriResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRegistryUri::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRegistryUriSuccess");
}

FString UK2BeamNode_ApiRequest_GetRegistryUri::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRegistryUriError");
}

FString UK2BeamNode_ApiRequest_GetRegistryUri::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRegistryUriComplete");
}

#undef LOCTEXT_NAMESPACE
