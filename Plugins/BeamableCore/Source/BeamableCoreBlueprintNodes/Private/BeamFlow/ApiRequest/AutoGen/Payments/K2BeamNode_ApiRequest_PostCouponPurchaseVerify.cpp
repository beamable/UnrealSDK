

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostCouponPurchaseVerify.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostCouponPurchaseVerifyRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostCouponPurchaseVerify"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostCouponPurchaseVerify::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostCouponPurchaseVerify::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostCouponPurchaseVerify);
}

FName UK2BeamNode_ApiRequest_PostCouponPurchaseVerify::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostCouponPurchaseVerifyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseVerify::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseVerify::GetEndpointName() const
{
	return TEXT("PostCouponPurchaseVerify");
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseVerify::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseVerify::GetRequestClass() const
{
	return UPostCouponPurchaseVerifyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseVerify::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseVerify::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostCouponPurchaseVerifySuccess");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseVerify::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostCouponPurchaseVerifyError");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseVerify::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostCouponPurchaseVerifyComplete");
}

#undef LOCTEXT_NAMESPACE
