

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsFillDeliveryOrdersRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/FillDeliveryOrdersResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, FillDeliveryOrders);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsFillDeliveryOrdersRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders::GetEndpointName() const
{
	return TEXT("FillDeliveryOrders");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders::GetRequestClass() const
{
	return UBeamFarmMsFillDeliveryOrdersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders::GetResponseClass() const
{
	return UFillDeliveryOrdersResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsFillDeliveryOrdersSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsFillDeliveryOrdersError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsFillDeliveryOrders::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsFillDeliveryOrdersComplete");
}

#undef LOCTEXT_NAMESPACE
