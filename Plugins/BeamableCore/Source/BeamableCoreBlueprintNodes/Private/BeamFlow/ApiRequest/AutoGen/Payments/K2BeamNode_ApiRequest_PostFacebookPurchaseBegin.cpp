

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostFacebookPurchaseBegin.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostFacebookPurchaseBeginRequest.h"
#include "BeamableCore/Public/AutoGen/BeginPurchaseResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostFacebookPurchaseBegin"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseBegin::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseBegin::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostFacebookPurchaseBegin);
}

FName UK2BeamNode_ApiRequest_PostFacebookPurchaseBegin::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostFacebookPurchaseBeginRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseBegin::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseBegin::GetEndpointName() const
{
	return TEXT("PostFacebookPurchaseBegin");
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseBegin::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseBegin::GetRequestClass() const
{
	return UPostFacebookPurchaseBeginRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookPurchaseBegin::GetResponseClass() const
{
	return UBeginPurchaseResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseBegin::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseBeginSuccess");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseBegin::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseBeginError");
}

FString UK2BeamNode_ApiRequest_PostFacebookPurchaseBegin::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostFacebookPurchaseBeginComplete");
}

#undef LOCTEXT_NAMESPACE
