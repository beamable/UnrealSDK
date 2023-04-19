

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostFacebookPurchaseFail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostFacebookPurchaseFailRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostFacebookPurchaseFail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseFail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseFail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostFacebookPurchaseFail);
}

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseFail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostFacebookPurchaseFailRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseFail::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseFail::GetEndpointName() const
{
	return TEXT("PostFacebookPurchaseFail");
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseFail::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseFail::GetRequestClass() const
{
	return UPostFacebookPurchaseFailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseFail::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseFail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseFailSuccess");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseFail::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseFailError");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseFail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseFailComplete");
}

#undef LOCTEXT_NAMESPACE
