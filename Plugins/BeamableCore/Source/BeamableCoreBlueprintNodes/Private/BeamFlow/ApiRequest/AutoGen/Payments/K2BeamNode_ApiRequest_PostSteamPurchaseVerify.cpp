

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostSteamPurchaseVerify.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostSteamPurchaseVerifyRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSteamPurchaseVerify"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSteamPurchaseVerify::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSteamPurchaseVerify::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostSteamPurchaseVerify);
}

FName UK2BeamNode_ApiRequest_PostSteamPurchaseVerify::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSteamPurchaseVerifyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseVerify::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseVerify::GetEndpointName() const
{
	return TEXT("PostSteamPurchaseVerify");
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseVerify::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseVerify::GetRequestClass() const
{
	return UPostSteamPurchaseVerifyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseVerify::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseVerify::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSteamPurchaseVerifySuccess");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseVerify::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSteamPurchaseVerifyError");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseVerify::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSteamPurchaseVerifyComplete");
}

#undef LOCTEXT_NAMESPACE
