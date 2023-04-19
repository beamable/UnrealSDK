

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostWindowsPurchaseFail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostWindowsPurchaseFailRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostWindowsPurchaseFail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseFail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseFail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostWindowsPurchaseFail);
}

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseFail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostWindowsPurchaseFailRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseFail::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseFail::GetEndpointName() const
{
	return TEXT("PostWindowsPurchaseFail");
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseFail::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseFail::GetRequestClass() const
{
	return UPostWindowsPurchaseFailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseFail::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseFail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseFailSuccess");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseFail::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseFailError");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseFail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseFailComplete");
}

#undef LOCTEXT_NAMESPACE
