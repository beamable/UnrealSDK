

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostSteamPurchaseComplete.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostSteamPurchaseCompleteRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSteamPurchaseComplete"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSteamPurchaseComplete::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSteamPurchaseComplete::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostSteamPurchaseComplete);
}

FName UK2BeamNode_ApiRequest_PostSteamPurchaseComplete::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSteamPurchaseCompleteRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseComplete::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseComplete::GetEndpointName() const
{
	return TEXT("PostSteamPurchaseComplete");
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseComplete::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseComplete::GetRequestClass() const
{
	return UPostSteamPurchaseCompleteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseComplete::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseComplete::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSteamPurchaseCompleteSuccess");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseComplete::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSteamPurchaseCompleteError");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseComplete::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSteamPurchaseCompleteComplete");
}

#undef LOCTEXT_NAMESPACE
