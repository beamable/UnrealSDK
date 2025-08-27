

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PostPromotion.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostPromotionRequest.h"
#include "BeamableCore/Public/AutoGen/PromoteRealmResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostPromotion"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostPromotion::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostPromotion::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PostPromotion);
}

FName UK2BeamNode_ApiRequest_PostPromotion::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostPromotionRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostPromotion::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PostPromotion::GetEndpointName() const
{
	return TEXT("PostPromotion");
}

UClass* UK2BeamNode_ApiRequest_PostPromotion::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPromotion::GetRequestClass() const
{
	return UPostPromotionRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPromotion::GetResponseClass() const
{
	return UPromoteRealmResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostPromotion::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostPromotionSuccess");
}

FString UK2BeamNode_ApiRequest_PostPromotion::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostPromotionError");
}

FString UK2BeamNode_ApiRequest_PostPromotion::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostPromotionComplete");
}

#undef LOCTEXT_NAMESPACE
