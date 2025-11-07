

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_BasicRealmsGetConfig.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/BasicRealmsGetConfigRequest.h"
#include "BeamableCore/Public/AutoGen/RealmConfigResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicRealmsGetConfig"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicRealmsGetConfig::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicRealmsGetConfig::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetConfig);
}

FName UK2BeamNode_ApiRequest_BasicRealmsGetConfig::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicRealmsGetConfigRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetConfig::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetConfig::GetEndpointName() const
{
	return TEXT("GetConfig");
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsGetConfig::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsGetConfig::GetRequestClass() const
{
	return UBasicRealmsGetConfigRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsGetConfig::GetResponseClass() const
{
	return URealmConfigResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetConfig::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicRealmsGetConfigSuccess");
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetConfig::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicRealmsGetConfigError");
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetConfig::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicRealmsGetConfigComplete");
}

#undef LOCTEXT_NAMESPACE
