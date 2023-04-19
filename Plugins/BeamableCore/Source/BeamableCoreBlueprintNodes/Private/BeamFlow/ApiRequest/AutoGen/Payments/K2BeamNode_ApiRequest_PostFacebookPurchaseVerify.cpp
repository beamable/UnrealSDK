

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostFacebookPurchaseVerify.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostFacebookPurchaseVerifyRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostFacebookPurchaseVerify"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseVerify::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseVerify::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostFacebookPurchaseVerify);
}

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseVerify::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostFacebookPurchaseVerifyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseVerify::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseVerify::GetEndpointName() const
{
	return TEXT("PostFacebookPurchaseVerify");
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseVerify::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseVerify::GetRequestClass() const
{
	return UPostFacebookPurchaseVerifyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseVerify::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseVerify::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseVerifySuccess");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseVerify::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseVerifyError");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseVerify::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseVerifyComplete");
}

#undef LOCTEXT_NAMESPACE
