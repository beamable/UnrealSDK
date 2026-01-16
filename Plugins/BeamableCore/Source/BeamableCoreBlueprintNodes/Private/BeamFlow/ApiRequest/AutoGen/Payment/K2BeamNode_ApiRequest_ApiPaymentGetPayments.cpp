

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payment/K2BeamNode_ApiRequest_ApiPaymentGetPayments.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/ApiPaymentGetPaymentsRequest.h"
#include "BeamableCore/Public/AutoGen/GetTransactionsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiPaymentGetPayments"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiPaymentGetPayments::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiPaymentGetPayments::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, GetPayments);
}

FName UK2BeamNode_ApiRequest_ApiPaymentGetPayments::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiPaymentGetPaymentsRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiPaymentGetPayments::GetServiceName() const
{
	return TEXT("Payment");
}

FString UK2BeamNode_ApiRequest_ApiPaymentGetPayments::GetEndpointName() const
{
	return TEXT("GetPayments");
}

UClass* UK2BeamNode_ApiRequest_ApiPaymentGetPayments::GetApiClass() const
{
	return UBeamPaymentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPaymentGetPayments::GetRequestClass() const
{
	return UApiPaymentGetPaymentsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPaymentGetPayments::GetResponseClass() const
{
	return UGetTransactionsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiPaymentGetPayments::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiPaymentGetPaymentsSuccess");
}

FString UK2BeamNode_ApiRequest_ApiPaymentGetPayments::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiPaymentGetPaymentsError");
}

FString UK2BeamNode_ApiRequest_ApiPaymentGetPayments::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiPaymentGetPaymentsComplete");
}

#undef LOCTEXT_NAMESPACE
