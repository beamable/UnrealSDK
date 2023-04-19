

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_GetAvailableDeviceId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAvailableDeviceIdRequest.h"
#include "BeamableCore/Public/AutoGen/AccountAvailableResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAvailableDeviceId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAvailableDeviceId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAvailableDeviceId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetAvailableDeviceId);
}

FName UK2BeamNode_ApiRequest_GetAvailableDeviceId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAvailableDeviceIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAvailableDeviceId::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_GetAvailableDeviceId::GetEndpointName() const
{
	return TEXT("GetAvailableDeviceId");
}

UClass* UK2BeamNode_ApiRequest_GetAvailableDeviceId::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailableDeviceId::GetRequestClass() const
{
	return UGetAvailableDeviceIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailableDeviceId::GetResponseClass() const
{
	return UAccountAvailableResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAvailableDeviceId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAvailableDeviceIdSuccess");
}

FString UK2BeamNode_ApiRequest_GetAvailableDeviceId::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAvailableDeviceIdError");
}

FString UK2BeamNode_ApiRequest_GetAvailableDeviceId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAvailableDeviceIdComplete");
}

#undef LOCTEXT_NAMESPACE
