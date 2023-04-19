

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostGoogleplayPurchaseVerifyRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostGoogleplayPurchaseVerify);
}

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostGoogleplayPurchaseVerifyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify::GetEndpointName() const
{
	return TEXT("PostGoogleplayPurchaseVerify");
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify::GetRequestClass() const
{
	return UPostGoogleplayPurchaseVerifyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseVerifySuccess");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseVerifyError");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseVerify::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseVerifyComplete");
}

#undef LOCTEXT_NAMESPACE
