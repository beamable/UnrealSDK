

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostItunesPurchaseFail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostItunesPurchaseFailRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostItunesPurchaseFail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostItunesPurchaseFail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostItunesPurchaseFail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostItunesPurchaseFail);
}

FName UK2BeamNode_ApiRequest_PostItunesPurchaseFail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostItunesPurchaseFailRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseFail::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseFail::GetEndpointName() const
{
	return TEXT("PostItunesPurchaseFail");
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseFail::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseFail::GetRequestClass() const
{
	return UPostItunesPurchaseFailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseFail::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseFail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostItunesPurchaseFailSuccess");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseFail::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostItunesPurchaseFailError");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseFail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostItunesPurchaseFailComplete");
}

#undef LOCTEXT_NAMESPACE
