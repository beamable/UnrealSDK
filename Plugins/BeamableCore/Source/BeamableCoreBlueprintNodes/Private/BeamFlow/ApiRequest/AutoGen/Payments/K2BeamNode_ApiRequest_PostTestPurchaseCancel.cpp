

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostTestPurchaseCancel.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostTestPurchaseCancelRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTestPurchaseCancel"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTestPurchaseCancel::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTestPurchaseCancel::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostTestPurchaseCancel);
}

FName UK2BeamNode_ApiRequest_PostTestPurchaseCancel::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTestPurchaseCancelRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseCancel::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseCancel::GetEndpointName() const
{
	return TEXT("PostTestPurchaseCancel");
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseCancel::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseCancel::GetRequestClass() const
{
	return UPostTestPurchaseCancelRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseCancel::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseCancel::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTestPurchaseCancelSuccess");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseCancel::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTestPurchaseCancelError");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseCancel::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTestPurchaseCancelComplete");
}

#undef LOCTEXT_NAMESPACE
