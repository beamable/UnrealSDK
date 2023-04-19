

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetRegistry.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetRegistryRequest.h"
#include "BeamableCore/Public/AutoGen/GetElasticContainerRegistryURI.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRegistry"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRegistry::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRegistry::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetRegistry);
}

FName UK2BeamNode_ApiRequest_GetRegistry::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRegistryRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRegistry::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetRegistry::GetEndpointName() const
{
	return TEXT("GetRegistry");
}

UClass* UK2BeamNode_ApiRequest_GetRegistry::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRegistry::GetRequestClass() const
{
	return UGetRegistryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRegistry::GetResponseClass() const
{
	return UGetElasticContainerRegistryURI::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRegistry::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRegistrySuccess");
}

FString UK2BeamNode_ApiRequest_GetRegistry::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRegistryError");
}

FString UK2BeamNode_ApiRequest_GetRegistry::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRegistryComplete");
}

#undef LOCTEXT_NAMESPACE
