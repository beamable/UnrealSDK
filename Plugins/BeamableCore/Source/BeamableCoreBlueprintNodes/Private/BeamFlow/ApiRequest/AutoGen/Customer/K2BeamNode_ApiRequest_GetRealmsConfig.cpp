

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_GetRealmsConfig.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/GetRealmsConfigRequest.h"
#include "BeamableCore/Public/AutoGen/RealmConfigResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRealmsConfig"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRealmsConfig::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRealmsConfig::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetRealmsConfig);
}

FName UK2BeamNode_ApiRequest_GetRealmsConfig::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRealmsConfigRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRealmsConfig::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_GetRealmsConfig::GetEndpointName() const
{
	return TEXT("GetRealmsConfig");
}

UClass* UK2BeamNode_ApiRequest_GetRealmsConfig::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRealmsConfig::GetRequestClass() const
{
	return UGetRealmsConfigRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRealmsConfig::GetResponseClass() const
{
	return URealmConfigResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRealmsConfig::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRealmsConfigSuccess");
}

FString UK2BeamNode_ApiRequest_GetRealmsConfig::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRealmsConfigError");
}

FString UK2BeamNode_ApiRequest_GetRealmsConfig::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRealmsConfigComplete");
}

#undef LOCTEXT_NAMESPACE
