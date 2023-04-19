

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostWindowsPurchaseVerify.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostWindowsPurchaseVerifyRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostWindowsPurchaseVerify"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseVerify::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseVerify::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostWindowsPurchaseVerify);
}

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseVerify::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostWindowsPurchaseVerifyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseVerify::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseVerify::GetEndpointName() const
{
	return TEXT("PostWindowsPurchaseVerify");
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseVerify::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseVerify::GetRequestClass() const
{
	return UPostWindowsPurchaseVerifyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseVerify::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseVerify::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseVerifySuccess");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseVerify::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseVerifyError");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseVerify::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseVerifyComplete");
}

#undef LOCTEXT_NAMESPACE
