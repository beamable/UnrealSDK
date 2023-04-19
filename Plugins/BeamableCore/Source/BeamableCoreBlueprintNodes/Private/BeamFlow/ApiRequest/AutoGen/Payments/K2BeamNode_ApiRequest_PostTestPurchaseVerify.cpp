

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostTestPurchaseVerify.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostTestPurchaseVerifyRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTestPurchaseVerify"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTestPurchaseVerify::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTestPurchaseVerify::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostTestPurchaseVerify);
}

FName UK2BeamNode_ApiRequest_PostTestPurchaseVerify::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTestPurchaseVerifyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseVerify::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseVerify::GetEndpointName() const
{
	return TEXT("PostTestPurchaseVerify");
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseVerify::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseVerify::GetRequestClass() const
{
	return UPostTestPurchaseVerifyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseVerify::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseVerify::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTestPurchaseVerifySuccess");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseVerify::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTestPurchaseVerifyError");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseVerify::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTestPurchaseVerifyComplete");
}

#undef LOCTEXT_NAMESPACE
