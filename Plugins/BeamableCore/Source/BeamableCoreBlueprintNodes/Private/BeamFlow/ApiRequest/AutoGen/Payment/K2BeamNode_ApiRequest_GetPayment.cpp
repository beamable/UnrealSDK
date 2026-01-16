

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payment/K2BeamNode_ApiRequest_GetPayment.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/GetPaymentRequest.h"
#include "BeamableCore/Public/AutoGen/Transaction.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetPayment"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetPayment::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetPayment::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, GetPayment);
}

FName UK2BeamNode_ApiRequest_GetPayment::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetPaymentRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetPayment::GetServiceName() const
{
	return TEXT("Payment");
}

FString UK2BeamNode_ApiRequest_GetPayment::GetEndpointName() const
{
	return TEXT("GetPayment");
}

UClass* UK2BeamNode_ApiRequest_GetPayment::GetApiClass() const
{
	return UBeamPaymentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPayment::GetRequestClass() const
{
	return UGetPaymentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPayment::GetResponseClass() const
{
	return UTransaction::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetPayment::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetPaymentSuccess");
}

FString UK2BeamNode_ApiRequest_GetPayment::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetPaymentError");
}

FString UK2BeamNode_ApiRequest_GetPayment::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetPaymentComplete");
}

#undef LOCTEXT_NAMESPACE
