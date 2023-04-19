

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostFacebookPurchaseTrack.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostFacebookPurchaseTrackRequest.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostFacebookPurchaseTrack"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseTrack::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseTrack::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostFacebookPurchaseTrack);
}

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseTrack::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostFacebookPurchaseTrackRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseTrack::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseTrack::GetEndpointName() const
{
	return TEXT("PostFacebookPurchaseTrack");
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseTrack::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseTrack::GetRequestClass() const
{
	return UPostFacebookPurchaseTrackRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseTrack::GetResponseClass() const
{
	return UPaymentResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseTrack::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseTrackSuccess");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseTrack::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseTrackError");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseTrack::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseTrackComplete");
}

#undef LOCTEXT_NAMESPACE
