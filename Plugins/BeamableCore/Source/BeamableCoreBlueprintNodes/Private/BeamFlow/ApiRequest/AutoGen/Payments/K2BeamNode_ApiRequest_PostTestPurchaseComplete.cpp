

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostTestPurchaseComplete.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostTestPurchaseCompleteRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTestPurchaseComplete"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTestPurchaseComplete::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTestPurchaseComplete::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostTestPurchaseComplete);
}

FName UK2BeamNode_ApiRequest_PostTestPurchaseComplete::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTestPurchaseCompleteRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseComplete::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseComplete::GetEndpointName() const
{
	return TEXT("PostTestPurchaseComplete");
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseComplete::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseComplete::GetRequestClass() const
{
	return UPostTestPurchaseCompleteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseComplete::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseComplete::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTestPurchaseCompleteSuccess");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseComplete::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTestPurchaseCompleteError");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseComplete::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTestPurchaseCompleteComplete");
}

#undef LOCTEXT_NAMESPACE
