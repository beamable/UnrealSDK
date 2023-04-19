

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostCouponPurchaseComplete.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostCouponPurchaseCompleteRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostCouponPurchaseComplete"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostCouponPurchaseComplete::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostCouponPurchaseComplete::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostCouponPurchaseComplete);
}

FName UK2BeamNode_ApiRequest_PostCouponPurchaseComplete::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostCouponPurchaseCompleteRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseComplete::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseComplete::GetEndpointName() const
{
	return TEXT("PostCouponPurchaseComplete");
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseComplete::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseComplete::GetRequestClass() const
{
	return UPostCouponPurchaseCompleteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseComplete::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseComplete::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostCouponPurchaseCompleteSuccess");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseComplete::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostCouponPurchaseCompleteError");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseComplete::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostCouponPurchaseCompleteComplete");
}

#undef LOCTEXT_NAMESPACE
