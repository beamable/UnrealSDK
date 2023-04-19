

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_GetCouponsCount.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/GetCouponsCountRequest.h"
#include "BeamableCore/Public/AutoGen/GetTotalCouponResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCouponsCount"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCouponsCount::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCouponsCount::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetCouponsCount);
}

FName UK2BeamNode_ApiRequest_GetCouponsCount::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCouponsCountRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCouponsCount::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_GetCouponsCount::GetEndpointName() const
{
	return TEXT("GetCouponsCount");
}

UClass* UK2BeamNode_ApiRequest_GetCouponsCount::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCouponsCount::GetRequestClass() const
{
	return UGetCouponsCountRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCouponsCount::GetResponseClass() const
{
	return UGetTotalCouponResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCouponsCount::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCouponsCountSuccess");
}

FString UK2BeamNode_ApiRequest_GetCouponsCount::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCouponsCountError");
}

FString UK2BeamNode_ApiRequest_GetCouponsCount::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCouponsCountComplete");
}

#undef LOCTEXT_NAMESPACE
