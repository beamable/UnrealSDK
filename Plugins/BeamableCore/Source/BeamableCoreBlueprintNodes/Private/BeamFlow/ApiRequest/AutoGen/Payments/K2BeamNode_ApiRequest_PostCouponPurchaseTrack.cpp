

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostCouponPurchaseTrack.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostCouponPurchaseTrackRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostCouponPurchaseTrack"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostCouponPurchaseTrack::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostCouponPurchaseTrack::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostCouponPurchaseTrack);
}

FName UK2BeamNode_ApiRequest_PostCouponPurchaseTrack::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostCouponPurchaseTrackRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseTrack::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseTrack::GetEndpointName() const
{
	return TEXT("PostCouponPurchaseTrack");
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseTrack::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseTrack::GetRequestClass() const
{
	return UPostCouponPurchaseTrackRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseTrack::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseTrack::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostCouponPurchaseTrackSuccess");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseTrack::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostCouponPurchaseTrackError");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseTrack::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostCouponPurchaseTrackComplete");
}

#undef LOCTEXT_NAMESPACE
