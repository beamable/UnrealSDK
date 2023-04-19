

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostSteamPurchaseFail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostSteamPurchaseFailRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSteamPurchaseFail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSteamPurchaseFail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSteamPurchaseFail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostSteamPurchaseFail);
}

FName UK2BeamNode_ApiRequest_PostSteamPurchaseFail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSteamPurchaseFailRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseFail::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseFail::GetEndpointName() const
{
	return TEXT("PostSteamPurchaseFail");
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseFail::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseFail::GetRequestClass() const
{
	return UPostSteamPurchaseFailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseFail::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseFail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSteamPurchaseFailSuccess");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseFail::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSteamPurchaseFailError");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseFail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSteamPurchaseFailComplete");
}

#undef LOCTEXT_NAMESPACE
