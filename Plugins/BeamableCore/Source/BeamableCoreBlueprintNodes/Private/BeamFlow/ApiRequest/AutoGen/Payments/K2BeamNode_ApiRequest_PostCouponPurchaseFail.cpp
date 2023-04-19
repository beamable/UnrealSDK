

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostCouponPurchaseFail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostCouponPurchaseFailRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostCouponPurchaseFail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostCouponPurchaseFail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostCouponPurchaseFail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostCouponPurchaseFail);
}

FName UK2BeamNode_ApiRequest_PostCouponPurchaseFail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostCouponPurchaseFailRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseFail::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseFail::GetEndpointName() const
{
	return TEXT("PostCouponPurchaseFail");
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseFail::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseFail::GetRequestClass() const
{
	return UPostCouponPurchaseFailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseFail::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseFail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostCouponPurchaseFailSuccess");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseFail::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostCouponPurchaseFailError");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseFail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostCouponPurchaseFailComplete");
}

#undef LOCTEXT_NAMESPACE
