

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostWindowsPurchaseComplete.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostWindowsPurchaseCompleteRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostWindowsPurchaseComplete"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseComplete::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseComplete::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostWindowsPurchaseComplete);
}

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseComplete::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostWindowsPurchaseCompleteRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseComplete::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseComplete::GetEndpointName() const
{
	return TEXT("PostWindowsPurchaseComplete");
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseComplete::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseComplete::GetRequestClass() const
{
	return UPostWindowsPurchaseCompleteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseComplete::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseComplete::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseCompleteSuccess");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseComplete::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseCompleteError");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseComplete::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseCompleteComplete");
}

#undef LOCTEXT_NAMESPACE
