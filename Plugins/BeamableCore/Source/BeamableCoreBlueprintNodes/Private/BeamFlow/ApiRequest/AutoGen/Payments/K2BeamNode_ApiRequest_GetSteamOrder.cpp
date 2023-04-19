

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetSteamOrder.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetSteamOrderRequest.h"
#include "BeamableCore/Public/AutoGen/SteamOrderInfoResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetSteamOrder"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetSteamOrder::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetSteamOrder::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSteamOrder);
}

FName UK2BeamNode_ApiRequest_GetSteamOrder::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetSteamOrderRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetSteamOrder::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetSteamOrder::GetEndpointName() const
{
	return TEXT("GetSteamOrder");
}

UClass* UK2BeamNode_ApiRequest_GetSteamOrder::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSteamOrder::GetRequestClass() const
{
	return UGetSteamOrderRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSteamOrder::GetResponseClass() const
{
	return USteamOrderInfoResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetSteamOrder::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetSteamOrderSuccess");
}

FString UK2BeamNode_ApiRequest_GetSteamOrder::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetSteamOrderError");
}

FString UK2BeamNode_ApiRequest_GetSteamOrder::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetSteamOrderComplete");
}

#undef LOCTEXT_NAMESPACE
