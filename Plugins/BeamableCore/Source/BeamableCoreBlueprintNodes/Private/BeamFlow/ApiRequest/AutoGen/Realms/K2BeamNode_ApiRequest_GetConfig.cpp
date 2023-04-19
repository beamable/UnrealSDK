

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetConfig.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetConfigRequest.h"
#include "BeamableCore/Public/AutoGen/RealmConfigResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetConfig"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetConfig::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetConfig::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetConfig);
}

FName UK2BeamNode_ApiRequest_GetConfig::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetConfigRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetConfig::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetConfig::GetEndpointName() const
{
	return TEXT("GetConfig");
}

UClass* UK2BeamNode_ApiRequest_GetConfig::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetConfig::GetRequestClass() const
{
	return UGetConfigRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetConfig::GetResponseClass() const
{
	return URealmConfigResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetConfig::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetConfigSuccess");
}

FString UK2BeamNode_ApiRequest_GetConfig::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetConfigError");
}

FString UK2BeamNode_ApiRequest_GetConfig::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetConfigComplete");
}

#undef LOCTEXT_NAMESPACE
