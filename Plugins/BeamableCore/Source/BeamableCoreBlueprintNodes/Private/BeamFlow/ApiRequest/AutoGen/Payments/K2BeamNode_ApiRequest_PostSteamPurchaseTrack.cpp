

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostSteamPurchaseTrack.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostSteamPurchaseTrackRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSteamPurchaseTrack"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSteamPurchaseTrack::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSteamPurchaseTrack::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostSteamPurchaseTrack);
}

FName UK2BeamNode_ApiRequest_PostSteamPurchaseTrack::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSteamPurchaseTrackRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseTrack::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseTrack::GetEndpointName() const
{
	return TEXT("PostSteamPurchaseTrack");
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseTrack::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseTrack::GetRequestClass() const
{
	return UPostSteamPurchaseTrackRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseTrack::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseTrack::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSteamPurchaseTrackSuccess");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseTrack::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSteamPurchaseTrackError");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseTrack::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSteamPurchaseTrackComplete");
}

#undef LOCTEXT_NAMESPACE
