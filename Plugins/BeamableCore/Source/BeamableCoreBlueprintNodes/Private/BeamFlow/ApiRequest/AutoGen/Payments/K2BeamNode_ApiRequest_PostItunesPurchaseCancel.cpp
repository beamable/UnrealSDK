

#include "BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostItunesPurchaseCancel.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamPaymentsApi.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseCancelRequest.h"
#include "AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostItunesPurchaseCancel"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostItunesPurchaseCancel::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostItunesPurchaseCancel::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostItunesPurchaseCancel);
}

FName UK2BeamNode_ApiRequest_PostItunesPurchaseCancel::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostItunesPurchaseCancelRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseCancel::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseCancel::GetEndpointName() const
{
	return TEXT("PostItunesPurchaseCancel");
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseCancel::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseCancel::GetRequestClass() const
{
	return UPostItunesPurchaseCancelRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseCancel::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseCancel::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostItunesPurchaseCancelSuccess");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseCancel::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostItunesPurchaseCancelError");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseCancel::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostItunesPurchaseCancelComplete");
}

#undef LOCTEXT_NAMESPACE
