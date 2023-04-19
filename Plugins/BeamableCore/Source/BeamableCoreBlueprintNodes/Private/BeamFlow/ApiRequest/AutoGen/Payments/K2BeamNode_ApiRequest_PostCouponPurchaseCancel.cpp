

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostCouponPurchaseCancel.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostCouponPurchaseCancelRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostCouponPurchaseCancel"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostCouponPurchaseCancel::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostCouponPurchaseCancel::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostCouponPurchaseCancel);
}

FName UK2BeamNode_ApiRequest_PostCouponPurchaseCancel::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostCouponPurchaseCancelRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseCancel::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseCancel::GetEndpointName() const
{
	return TEXT("PostCouponPurchaseCancel");
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseCancel::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseCancel::GetRequestClass() const
{
	return UPostCouponPurchaseCancelRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseCancel::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseCancel::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostCouponPurchaseCancelSuccess");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseCancel::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostCouponPurchaseCancelError");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseCancel::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostCouponPurchaseCancelComplete");
}

#undef LOCTEXT_NAMESPACE
