

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/SuiFederation/K2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamSuiFederationApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/SuiFederation/SuiFederationGetSuiEnvironmentRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SuiFederationGetSuiEnvironmentResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSuiFederationApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSuiFederationApi, GetSuiEnvironment);
}

FName UK2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(USuiFederationGetSuiEnvironmentRequest, Make);
}

FString UK2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment::GetServiceName() const
{
	return TEXT("SuiFederation");
}

FString UK2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment::GetEndpointName() const
{
	return TEXT("GetSuiEnvironment");
}

UClass* UK2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment::GetApiClass() const
{
	return UBeamSuiFederationApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment::GetRequestClass() const
{
	return USuiFederationGetSuiEnvironmentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment::GetResponseClass() const
{
	return USuiFederationGetSuiEnvironmentResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment::GetRequestSuccessDelegateName() const
{
	return TEXT("OnSuiFederationGetSuiEnvironmentSuccess");
}

FString UK2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment::GetRequestErrorDelegateName() const
{
	return TEXT("OnSuiFederationGetSuiEnvironmentError");
}

FString UK2BeamNode_ApiRequest_SuiFederationGetSuiEnvironment::GetRequestCompleteDelegateName() const
{
	return TEXT("OnSuiFederationGetSuiEnvironmentComplete");
}

#undef LOCTEXT_NAMESPACE
