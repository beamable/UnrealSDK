

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostSteamPurchaseCancel.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostSteamPurchaseCancelRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSteamPurchaseCancel"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSteamPurchaseCancel::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSteamPurchaseCancel::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostSteamPurchaseCancel);
}

FName UK2BeamNode_ApiRequest_PostSteamPurchaseCancel::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSteamPurchaseCancelRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseCancel::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseCancel::GetEndpointName() const
{
	return TEXT("PostSteamPurchaseCancel");
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseCancel::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseCancel::GetRequestClass() const
{
	return UPostSteamPurchaseCancelRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseCancel::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseCancel::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSteamPurchaseCancelSuccess");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseCancel::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSteamPurchaseCancelError");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseCancel::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSteamPurchaseCancelComplete");
}

#undef LOCTEXT_NAMESPACE
