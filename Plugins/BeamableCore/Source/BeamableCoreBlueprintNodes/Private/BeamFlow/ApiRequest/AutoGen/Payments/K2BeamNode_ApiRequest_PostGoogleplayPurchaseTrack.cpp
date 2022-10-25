

#include "BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamPaymentsApi.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseTrackRequest.h"
#include "AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostGoogleplayPurchaseTrack);
}

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostGoogleplayPurchaseTrackRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack::GetEndpointName() const
{
	return TEXT("PostGoogleplayPurchaseTrack");
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack::GetRequestClass() const
{
	return UPostGoogleplayPurchaseTrackRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseTrackSuccess");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseTrackError");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseTrack::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseTrackComplete");
}

#undef LOCTEXT_NAMESPACE
