

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_GetRealmsPromotion.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/GetRealmsPromotionRequest.h"
#include "BeamableCore/Public/AutoGen/CustomerActorPromoteRealmResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRealmsPromotion"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRealmsPromotion::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRealmsPromotion::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetRealmsPromotion);
}

FName UK2BeamNode_ApiRequest_GetRealmsPromotion::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRealmsPromotionRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRealmsPromotion::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_GetRealmsPromotion::GetEndpointName() const
{
	return TEXT("GetRealmsPromotion");
}

UClass* UK2BeamNode_ApiRequest_GetRealmsPromotion::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRealmsPromotion::GetRequestClass() const
{
	return UGetRealmsPromotionRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRealmsPromotion::GetResponseClass() const
{
	return UCustomerActorPromoteRealmResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRealmsPromotion::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRealmsPromotionSuccess");
}

FString UK2BeamNode_ApiRequest_GetRealmsPromotion::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRealmsPromotionError");
}

FString UK2BeamNode_ApiRequest_GetRealmsPromotion::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRealmsPromotionComplete");
}

#undef LOCTEXT_NAMESPACE
