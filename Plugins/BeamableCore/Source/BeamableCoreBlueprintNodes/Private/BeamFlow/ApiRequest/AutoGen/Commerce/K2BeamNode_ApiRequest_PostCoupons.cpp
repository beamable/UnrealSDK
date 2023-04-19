

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_PostCoupons.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/PostCouponsRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostCoupons"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostCoupons::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostCoupons::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, PostCoupons);
}

FName UK2BeamNode_ApiRequest_PostCoupons::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostCouponsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostCoupons::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_PostCoupons::GetEndpointName() const
{
	return TEXT("PostCoupons");
}

UClass* UK2BeamNode_ApiRequest_PostCoupons::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCoupons::GetRequestClass() const
{
	return UPostCouponsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCoupons::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostCoupons::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostCouponsSuccess");
}

FString UK2BeamNode_ApiRequest_PostCoupons::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostCouponsError");
}

FString UK2BeamNode_ApiRequest_PostCoupons::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostCouponsComplete");
}

#undef LOCTEXT_NAMESPACE
