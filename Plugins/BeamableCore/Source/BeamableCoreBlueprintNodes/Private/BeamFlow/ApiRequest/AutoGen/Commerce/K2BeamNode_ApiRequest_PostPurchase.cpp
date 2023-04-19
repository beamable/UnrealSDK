

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_PostPurchase.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/PostPurchaseRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostPurchase"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostPurchase::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostPurchase::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, PostPurchase);
}

FName UK2BeamNode_ApiRequest_PostPurchase::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostPurchaseRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostPurchase::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_PostPurchase::GetEndpointName() const
{
	return TEXT("PostPurchase");
}

UClass* UK2BeamNode_ApiRequest_PostPurchase::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPurchase::GetRequestClass() const
{
	return UPostPurchaseRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPurchase::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostPurchase::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostPurchaseSuccess");
}

FString UK2BeamNode_ApiRequest_PostPurchase::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostPurchaseError");
}

FString UK2BeamNode_ApiRequest_PostPurchase::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostPurchaseComplete");
}

#undef LOCTEXT_NAMESPACE
