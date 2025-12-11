

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payment/K2BeamNode_ApiRequest_PutPayment.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/PutPaymentRequest.h"
#include "BeamableCore/Public/AutoGen/Transaction.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutPayment"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutPayment::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutPayment::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, PutPayment);
}

FName UK2BeamNode_ApiRequest_PutPayment::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutPaymentRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutPayment::GetServiceName() const
{
	return TEXT("Payment");
}

FString UK2BeamNode_ApiRequest_PutPayment::GetEndpointName() const
{
	return TEXT("PutPayment");
}

UClass* UK2BeamNode_ApiRequest_PutPayment::GetApiClass() const
{
	return UBeamPaymentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPayment::GetRequestClass() const
{
	return UPutPaymentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPayment::GetResponseClass() const
{
	return UTransaction::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutPayment::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutPaymentSuccess");
}

FString UK2BeamNode_ApiRequest_PutPayment::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutPaymentError");
}

FString UK2BeamNode_ApiRequest_PutPayment::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutPaymentComplete");
}

#undef LOCTEXT_NAMESPACE
