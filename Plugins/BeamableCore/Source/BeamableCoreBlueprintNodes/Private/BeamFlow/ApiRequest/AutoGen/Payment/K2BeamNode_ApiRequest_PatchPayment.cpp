

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payment/K2BeamNode_ApiRequest_PatchPayment.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/PatchPaymentRequest.h"
#include "BeamableCore/Public/AutoGen/Transaction.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PatchPayment"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PatchPayment::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PatchPayment::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, PatchPayment);
}

FName UK2BeamNode_ApiRequest_PatchPayment::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPatchPaymentRequest, Make);
}

FString UK2BeamNode_ApiRequest_PatchPayment::GetServiceName() const
{
	return TEXT("Payment");
}

FString UK2BeamNode_ApiRequest_PatchPayment::GetEndpointName() const
{
	return TEXT("PatchPayment");
}

UClass* UK2BeamNode_ApiRequest_PatchPayment::GetApiClass() const
{
	return UBeamPaymentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PatchPayment::GetRequestClass() const
{
	return UPatchPaymentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PatchPayment::GetResponseClass() const
{
	return UTransaction::StaticClass();
}

FString UK2BeamNode_ApiRequest_PatchPayment::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPatchPaymentSuccess");
}

FString UK2BeamNode_ApiRequest_PatchPayment::GetRequestErrorDelegateName() const
{
	return TEXT("OnPatchPaymentError");
}

FString UK2BeamNode_ApiRequest_PatchPayment::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPatchPaymentComplete");
}

#undef LOCTEXT_NAMESPACE
