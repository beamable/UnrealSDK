

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_DeleteMeDevice.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/DeleteMeDeviceRequest.h"
#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteMeDevice"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteMeDevice::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteMeDevice::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, DeleteMeDevice);
}

FName UK2BeamNode_ApiRequest_DeleteMeDevice::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteMeDeviceRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteMeDevice::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_DeleteMeDevice::GetEndpointName() const
{
	return TEXT("DeleteMeDevice");
}

UClass* UK2BeamNode_ApiRequest_DeleteMeDevice::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteMeDevice::GetRequestClass() const
{
	return UDeleteMeDeviceRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteMeDevice::GetResponseClass() const
{
	return UAccountPlayerView::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteMeDevice::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteMeDeviceSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteMeDevice::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteMeDeviceError");
}

FString UK2BeamNode_ApiRequest_DeleteMeDevice::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteMeDeviceComplete");
}

#undef LOCTEXT_NAMESPACE
