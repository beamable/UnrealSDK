

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostFacebookPurchaseComplete.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostFacebookPurchaseCompleteRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostFacebookPurchaseComplete"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseComplete::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseComplete::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostFacebookPurchaseComplete);
}

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseComplete::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostFacebookPurchaseCompleteRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseComplete::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseComplete::GetEndpointName() const
{
	return TEXT("PostFacebookPurchaseComplete");
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseComplete::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseComplete::GetRequestClass() const
{
	return UPostFacebookPurchaseCompleteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseComplete::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseComplete::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseCompleteSuccess");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseComplete::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseCompleteError");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseComplete::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseCompleteComplete");
}

#undef LOCTEXT_NAMESPACE
