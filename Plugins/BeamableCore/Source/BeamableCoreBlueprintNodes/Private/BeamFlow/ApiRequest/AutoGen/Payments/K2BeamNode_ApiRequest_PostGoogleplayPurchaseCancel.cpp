

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostGoogleplayPurchaseCancelRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostGoogleplayPurchaseCancel);
}

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostGoogleplayPurchaseCancelRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel::GetEndpointName() const
{
	return TEXT("PostGoogleplayPurchaseCancel");
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel::GetRequestClass() const
{
	return UPostGoogleplayPurchaseCancelRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseCancelSuccess");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseCancelError");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseCancel::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseCancelComplete");
}

#undef LOCTEXT_NAMESPACE
