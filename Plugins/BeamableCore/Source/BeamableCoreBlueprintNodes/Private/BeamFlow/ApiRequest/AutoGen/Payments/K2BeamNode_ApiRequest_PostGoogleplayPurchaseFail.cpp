

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostGoogleplayPurchaseFail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostGoogleplayPurchaseFailRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostGoogleplayPurchaseFail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseFail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseFail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostGoogleplayPurchaseFail);
}

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseFail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostGoogleplayPurchaseFailRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseFail::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseFail::GetEndpointName() const
{
	return TEXT("PostGoogleplayPurchaseFail");
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseFail::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseFail::GetRequestClass() const
{
	return UPostGoogleplayPurchaseFailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseFail::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseFail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseFailSuccess");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseFail::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseFailError");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseFail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseFailComplete");
}

#undef LOCTEXT_NAMESPACE
