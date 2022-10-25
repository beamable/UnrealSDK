

#include "BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamPaymentsApi.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseCompleteRequest.h"
#include "AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostGoogleplayPurchaseComplete);
}

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostGoogleplayPurchaseCompleteRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete::GetEndpointName() const
{
	return TEXT("PostGoogleplayPurchaseComplete");
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete::GetRequestClass() const
{
	return UPostGoogleplayPurchaseCompleteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseCompleteSuccess");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseCompleteError");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseComplete::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseCompleteComplete");
}

#undef LOCTEXT_NAMESPACE
