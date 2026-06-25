

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsListMyDevices.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsListMyDevicesRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeviceList.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsListMyDevices"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsListMyDevices::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsListMyDevices::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, ListMyDevices);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsListMyDevices::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsListMyDevicesRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsListMyDevices::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsListMyDevices::GetEndpointName() const
{
	return TEXT("ListMyDevices");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsListMyDevices::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsListMyDevices::GetRequestClass() const
{
	return UBeamFarmMsListMyDevicesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsListMyDevices::GetResponseClass() const
{
	return UDeviceList::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsListMyDevices::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsListMyDevicesSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsListMyDevices::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsListMyDevicesError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsListMyDevices::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsListMyDevicesComplete");
}

#undef LOCTEXT_NAMESPACE
