

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostWindowsPurchaseTrack.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostWindowsPurchaseTrackRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostWindowsPurchaseTrack"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseTrack::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseTrack::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostWindowsPurchaseTrack);
}

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseTrack::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostWindowsPurchaseTrackRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseTrack::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseTrack::GetEndpointName() const
{
	return TEXT("PostWindowsPurchaseTrack");
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseTrack::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseTrack::GetRequestClass() const
{
	return UPostWindowsPurchaseTrackRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseTrack::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseTrack::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseTrackSuccess");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseTrack::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseTrackError");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseTrack::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseTrackComplete");
}

#undef LOCTEXT_NAMESPACE
