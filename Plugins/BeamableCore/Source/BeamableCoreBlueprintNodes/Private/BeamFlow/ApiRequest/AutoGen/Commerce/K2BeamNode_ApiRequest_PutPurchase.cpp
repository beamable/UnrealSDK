

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_PutPurchase.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/PutPurchaseRequest.h"
#include "BeamableCore/Public/AutoGen/ResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutPurchase"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutPurchase::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutPurchase::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, PutPurchase);
}

FName UK2BeamNode_ApiRequest_PutPurchase::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutPurchaseRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutPurchase::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_PutPurchase::GetEndpointName() const
{
	return TEXT("PutPurchase");
}

UClass* UK2BeamNode_ApiRequest_PutPurchase::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPurchase::GetRequestClass() const
{
	return UPutPurchaseRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPurchase::GetResponseClass() const
{
	return UResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutPurchase::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutPurchaseSuccess");
}

FString UK2BeamNode_ApiRequest_PutPurchase::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutPurchaseError");
}

FString UK2BeamNode_ApiRequest_PutPurchase::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutPurchaseComplete");
}

#undef LOCTEXT_NAMESPACE
