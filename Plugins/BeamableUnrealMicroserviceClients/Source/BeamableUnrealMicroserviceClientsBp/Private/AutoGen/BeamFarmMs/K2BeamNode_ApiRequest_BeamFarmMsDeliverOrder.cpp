

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsDeliverOrder.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsDeliverOrderRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliverOrderResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsDeliverOrder"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsDeliverOrder::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsDeliverOrder::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, DeliverOrder);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsDeliverOrder::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsDeliverOrderRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsDeliverOrder::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsDeliverOrder::GetEndpointName() const
{
	return TEXT("DeliverOrder");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsDeliverOrder::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsDeliverOrder::GetRequestClass() const
{
	return UBeamFarmMsDeliverOrderRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsDeliverOrder::GetResponseClass() const
{
	return UDeliverOrderResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsDeliverOrder::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsDeliverOrderSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsDeliverOrder::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsDeliverOrderError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsDeliverOrder::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsDeliverOrderComplete");
}

#undef LOCTEXT_NAMESPACE
