

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PostRealmsPromotion.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PostRealmsPromotionRequest.h"
#include "BeamableCore/Public/AutoGen/CustomerActorPromoteRealmResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostRealmsPromotion"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostRealmsPromotion::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostRealmsPromotion::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PostRealmsPromotion);
}

FName UK2BeamNode_ApiRequest_PostRealmsPromotion::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostRealmsPromotionRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostRealmsPromotion::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PostRealmsPromotion::GetEndpointName() const
{
	return TEXT("PostRealmsPromotion");
}

UClass* UK2BeamNode_ApiRequest_PostRealmsPromotion::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostRealmsPromotion::GetRequestClass() const
{
	return UPostRealmsPromotionRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostRealmsPromotion::GetResponseClass() const
{
	return UCustomerActorPromoteRealmResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostRealmsPromotion::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostRealmsPromotionSuccess");
}

FString UK2BeamNode_ApiRequest_PostRealmsPromotion::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostRealmsPromotionError");
}

FString UK2BeamNode_ApiRequest_PostRealmsPromotion::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostRealmsPromotionComplete");
}

#undef LOCTEXT_NAMESPACE
