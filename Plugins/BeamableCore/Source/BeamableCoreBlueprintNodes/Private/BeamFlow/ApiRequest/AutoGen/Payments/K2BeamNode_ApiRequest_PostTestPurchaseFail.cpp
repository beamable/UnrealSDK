

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostTestPurchaseFail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostTestPurchaseFailRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTestPurchaseFail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTestPurchaseFail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTestPurchaseFail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostTestPurchaseFail);
}

FName UK2BeamNode_ApiRequest_PostTestPurchaseFail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTestPurchaseFailRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseFail::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseFail::GetEndpointName() const
{
	return TEXT("PostTestPurchaseFail");
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseFail::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseFail::GetRequestClass() const
{
	return UPostTestPurchaseFailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseFail::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseFail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTestPurchaseFailSuccess");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseFail::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTestPurchaseFailError");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseFail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTestPurchaseFailComplete");
}

#undef LOCTEXT_NAMESPACE
