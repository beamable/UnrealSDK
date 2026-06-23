

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsRegisterGroundItemRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterGroundItemResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, RegisterGroundItem);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsRegisterGroundItemRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem::GetEndpointName() const
{
	return TEXT("RegisterGroundItem");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem::GetRequestClass() const
{
	return UBeamFarmMsRegisterGroundItemRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem::GetResponseClass() const
{
	return URegisterGroundItemResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsRegisterGroundItemSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsRegisterGroundItemError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsRegisterGroundItem::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsRegisterGroundItemComplete");
}

#undef LOCTEXT_NAMESPACE
