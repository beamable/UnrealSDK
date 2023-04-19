

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostItunesPurchaseComplete.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostItunesPurchaseCompleteRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostItunesPurchaseComplete"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostItunesPurchaseComplete::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostItunesPurchaseComplete::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostItunesPurchaseComplete);
}

FName UK2BeamNode_ApiRequest_PostItunesPurchaseComplete::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostItunesPurchaseCompleteRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseComplete::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseComplete::GetEndpointName() const
{
	return TEXT("PostItunesPurchaseComplete");
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseComplete::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseComplete::GetRequestClass() const
{
	return UPostItunesPurchaseCompleteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseComplete::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseComplete::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostItunesPurchaseCompleteSuccess");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseComplete::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostItunesPurchaseCompleteError");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseComplete::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostItunesPurchaseCompleteComplete");
}

#undef LOCTEXT_NAMESPACE
