

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetPromotion.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetPromotionRequest.h"
#include "BeamableCore/Public/AutoGen/PromoteRealmResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetPromotion"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetPromotion::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetPromotion::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetPromotion);
}

FName UK2BeamNode_ApiRequest_GetPromotion::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetPromotionRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetPromotion::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetPromotion::GetEndpointName() const
{
	return TEXT("GetPromotion");
}

UClass* UK2BeamNode_ApiRequest_GetPromotion::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPromotion::GetRequestClass() const
{
	return UGetPromotionRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPromotion::GetResponseClass() const
{
	return UPromoteRealmResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetPromotion::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetPromotionSuccess");
}

FString UK2BeamNode_ApiRequest_GetPromotion::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetPromotionError");
}

FString UK2BeamNode_ApiRequest_GetPromotion::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetPromotionComplete");
}

#undef LOCTEXT_NAMESPACE
