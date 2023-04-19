

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostItunesPurchaseTrack.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostItunesPurchaseTrackRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostItunesPurchaseTrack"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostItunesPurchaseTrack::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostItunesPurchaseTrack::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostItunesPurchaseTrack);
}

FName UK2BeamNode_ApiRequest_PostItunesPurchaseTrack::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostItunesPurchaseTrackRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseTrack::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseTrack::GetEndpointName() const
{
	return TEXT("PostItunesPurchaseTrack");
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseTrack::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseTrack::GetRequestClass() const
{
	return UPostItunesPurchaseTrackRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseTrack::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseTrack::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostItunesPurchaseTrackSuccess");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseTrack::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostItunesPurchaseTrackError");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseTrack::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostItunesPurchaseTrackComplete");
}

#undef LOCTEXT_NAMESPACE
