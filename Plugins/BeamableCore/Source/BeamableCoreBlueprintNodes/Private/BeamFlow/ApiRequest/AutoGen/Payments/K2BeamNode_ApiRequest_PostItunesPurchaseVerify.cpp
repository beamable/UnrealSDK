

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostItunesPurchaseVerify.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostItunesPurchaseVerifyRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostItunesPurchaseVerify"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostItunesPurchaseVerify::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostItunesPurchaseVerify::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostItunesPurchaseVerify);
}

FName UK2BeamNode_ApiRequest_PostItunesPurchaseVerify::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostItunesPurchaseVerifyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseVerify::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseVerify::GetEndpointName() const
{
	return TEXT("PostItunesPurchaseVerify");
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseVerify::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseVerify::GetRequestClass() const
{
	return UPostItunesPurchaseVerifyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseVerify::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseVerify::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostItunesPurchaseVerifySuccess");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseVerify::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostItunesPurchaseVerifyError");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseVerify::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostItunesPurchaseVerifyComplete");
}

#undef LOCTEXT_NAMESPACE
