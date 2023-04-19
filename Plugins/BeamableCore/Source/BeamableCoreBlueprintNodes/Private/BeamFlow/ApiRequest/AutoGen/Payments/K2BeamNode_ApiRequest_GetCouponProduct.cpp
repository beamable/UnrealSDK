

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetCouponProduct.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetCouponProductRequest.h"
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCouponProduct"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCouponProduct::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCouponProduct::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetCouponProduct);
}

FName UK2BeamNode_ApiRequest_GetCouponProduct::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCouponProductRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCouponProduct::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetCouponProduct::GetEndpointName() const
{
	return TEXT("GetCouponProduct");
}

UClass* UK2BeamNode_ApiRequest_GetCouponProduct::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCouponProduct::GetRequestClass() const
{
	return UGetCouponProductRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCouponProduct::GetResponseClass() const
{
	return UGetProductResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCouponProduct::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCouponProductSuccess");
}

FString UK2BeamNode_ApiRequest_GetCouponProduct::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCouponProductError");
}

FString UK2BeamNode_ApiRequest_GetCouponProduct::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCouponProductComplete");
}

#undef LOCTEXT_NAMESPACE
