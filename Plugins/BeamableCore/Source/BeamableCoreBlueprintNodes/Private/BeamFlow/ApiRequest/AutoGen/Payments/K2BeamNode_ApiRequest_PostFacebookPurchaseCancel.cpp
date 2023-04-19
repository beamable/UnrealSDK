

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostFacebookPurchaseCancel.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostFacebookPurchaseCancelRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostFacebookPurchaseCancel"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseCancel::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseCancel::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostFacebookPurchaseCancel);
}

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseCancel::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostFacebookPurchaseCancelRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseCancel::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseCancel::GetEndpointName() const
{
	return TEXT("PostFacebookPurchaseCancel");
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseCancel::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseCancel::GetRequestClass() const
{
	return UPostFacebookPurchaseCancelRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseCancel::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseCancel::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseCancelSuccess");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseCancel::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseCancelError");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseCancel::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseCancelComplete");
}

#undef LOCTEXT_NAMESPACE
