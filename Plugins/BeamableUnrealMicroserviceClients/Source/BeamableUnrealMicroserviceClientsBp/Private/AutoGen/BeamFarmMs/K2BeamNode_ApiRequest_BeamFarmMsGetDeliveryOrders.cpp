

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsGetDeliveryOrdersRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetDeliveryOrdersResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetDeliveryOrders);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsGetDeliveryOrdersRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders::GetEndpointName() const
{
	return TEXT("GetDeliveryOrders");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders::GetRequestClass() const
{
	return UBeamFarmMsGetDeliveryOrdersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders::GetResponseClass() const
{
	return UGetDeliveryOrdersResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsGetDeliveryOrdersSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsGetDeliveryOrdersError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetDeliveryOrders::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsGetDeliveryOrdersComplete");
}

#undef LOCTEXT_NAMESPACE
