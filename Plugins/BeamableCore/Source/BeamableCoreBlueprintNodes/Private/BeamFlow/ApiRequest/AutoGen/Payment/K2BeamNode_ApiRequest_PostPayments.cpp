

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payment/K2BeamNode_ApiRequest_PostPayments.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/PostPaymentsRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostPayments"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostPayments::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostPayments::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, PostPayments);
}

FName UK2BeamNode_ApiRequest_PostPayments::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostPaymentsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostPayments::GetServiceName() const
{
	return TEXT("Payment");
}

FString UK2BeamNode_ApiRequest_PostPayments::GetEndpointName() const
{
	return TEXT("PostPayments");
}

UClass* UK2BeamNode_ApiRequest_PostPayments::GetApiClass() const
{
	return UBeamPaymentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPayments::GetRequestClass() const
{
	return UPostPaymentsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPayments::GetResponseClass() const
{
	return UPaymentResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostPayments::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostPaymentsSuccess");
}

FString UK2BeamNode_ApiRequest_PostPayments::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostPaymentsError");
}

FString UK2BeamNode_ApiRequest_PostPayments::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostPaymentsComplete");
}

#undef LOCTEXT_NAMESPACE
