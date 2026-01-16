

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payment/K2BeamNode_ApiRequest_DeletePayment.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/DeletePaymentRequest.h"
#include "BeamableCore/Public/AutoGen/Transaction.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeletePayment"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeletePayment::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeletePayment::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, DeletePayment);
}

FName UK2BeamNode_ApiRequest_DeletePayment::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeletePaymentRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeletePayment::GetServiceName() const
{
	return TEXT("Payment");
}

FString UK2BeamNode_ApiRequest_DeletePayment::GetEndpointName() const
{
	return TEXT("DeletePayment");
}

UClass* UK2BeamNode_ApiRequest_DeletePayment::GetApiClass() const
{
	return UBeamPaymentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeletePayment::GetRequestClass() const
{
	return UDeletePaymentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeletePayment::GetResponseClass() const
{
	return UTransaction::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeletePayment::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeletePaymentSuccess");
}

FString UK2BeamNode_ApiRequest_DeletePayment::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeletePaymentError");
}

FString UK2BeamNode_ApiRequest_DeletePayment::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeletePaymentComplete");
}

#undef LOCTEXT_NAMESPACE
