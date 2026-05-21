

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsCollectGroundItemRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectGroundItemResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, CollectGroundItem);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsCollectGroundItemRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem::GetEndpointName() const
{
	return TEXT("CollectGroundItem");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem::GetRequestClass() const
{
	return UBeamFarmMsCollectGroundItemRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem::GetResponseClass() const
{
	return UCollectGroundItemResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsCollectGroundItemSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsCollectGroundItemError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCollectGroundItem::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsCollectGroundItemComplete");
}

#undef LOCTEXT_NAMESPACE
