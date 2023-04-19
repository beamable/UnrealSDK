

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostTestPurchaseTrack.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostTestPurchaseTrackRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTestPurchaseTrack"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTestPurchaseTrack::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTestPurchaseTrack::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostTestPurchaseTrack);
}

FName UK2BeamNode_ApiRequest_PostTestPurchaseTrack::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTestPurchaseTrackRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseTrack::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseTrack::GetEndpointName() const
{
	return TEXT("PostTestPurchaseTrack");
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseTrack::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseTrack::GetRequestClass() const
{
	return UPostTestPurchaseTrackRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseTrack::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseTrack::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTestPurchaseTrackSuccess");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseTrack::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTestPurchaseTrackError");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseTrack::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTestPurchaseTrackComplete");
}

#undef LOCTEXT_NAMESPACE
