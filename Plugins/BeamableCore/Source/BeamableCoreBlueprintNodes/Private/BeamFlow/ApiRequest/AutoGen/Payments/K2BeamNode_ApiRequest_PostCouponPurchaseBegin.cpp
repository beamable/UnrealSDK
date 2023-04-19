

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostCouponPurchaseBegin.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostCouponPurchaseBeginRequest.h"
#include "BeamableCore/Public/AutoGen/BeginPurchaseResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostCouponPurchaseBegin"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostCouponPurchaseBegin::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostCouponPurchaseBegin::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostCouponPurchaseBegin);
}

FName UK2BeamNode_ApiRequest_PostCouponPurchaseBegin::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostCouponPurchaseBeginRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseBegin::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseBegin::GetEndpointName() const
{
	return TEXT("PostCouponPurchaseBegin");
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseBegin::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseBegin::GetRequestClass() const
{
	return UPostCouponPurchaseBeginRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCouponPurchaseBegin::GetResponseClass() const
{
	return UBeginPurchaseResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseBegin::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostCouponPurchaseBeginSuccess");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseBegin::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostCouponPurchaseBeginError");
}

FString UK2BeamNode_ApiRequest_PostCouponPurchaseBegin::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostCouponPurchaseBeginComplete");
}

#undef LOCTEXT_NAMESPACE
