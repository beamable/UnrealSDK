

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_GetOpenidConfiguration.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/GetOpenidConfigurationRequest.h"
#include "BeamableCore/Public/AutoGen/AuthV2OpenIdConfigResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetOpenidConfiguration"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetOpenidConfiguration::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetOpenidConfiguration::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetOpenidConfiguration);
}

FName UK2BeamNode_ApiRequest_GetOpenidConfiguration::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetOpenidConfigurationRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetOpenidConfiguration::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_GetOpenidConfiguration::GetEndpointName() const
{
	return TEXT("GetOpenidConfiguration");
}

UClass* UK2BeamNode_ApiRequest_GetOpenidConfiguration::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetOpenidConfiguration::GetRequestClass() const
{
	return UGetOpenidConfigurationRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetOpenidConfiguration::GetResponseClass() const
{
	return UAuthV2OpenIdConfigResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetOpenidConfiguration::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetOpenidConfigurationSuccess");
}

FString UK2BeamNode_ApiRequest_GetOpenidConfiguration::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetOpenidConfigurationError");
}

FString UK2BeamNode_ApiRequest_GetOpenidConfiguration::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetOpenidConfigurationComplete");
}

#undef LOCTEXT_NAMESPACE
