

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostWindowsPurchaseCancel.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostWindowsPurchaseCancelRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostWindowsPurchaseCancel"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseCancel::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseCancel::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostWindowsPurchaseCancel);
}

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseCancel::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostWindowsPurchaseCancelRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseCancel::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseCancel::GetEndpointName() const
{
	return TEXT("PostWindowsPurchaseCancel");
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseCancel::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseCancel::GetRequestClass() const
{
	return UPostWindowsPurchaseCancelRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseCancel::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseCancel::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseCancelSuccess");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseCancel::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseCancelError");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseCancel::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseCancelComplete");
}

#undef LOCTEXT_NAMESPACE
