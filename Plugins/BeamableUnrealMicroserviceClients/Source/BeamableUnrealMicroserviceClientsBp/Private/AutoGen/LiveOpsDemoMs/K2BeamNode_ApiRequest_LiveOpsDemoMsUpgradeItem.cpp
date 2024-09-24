

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/LiveOpsDemoMs/K2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamLiveOpsDemoMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMs/LiveOpsDemoMsUpgradeItemRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsUpgradeItemResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMsApi, UpgradeItem);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(ULiveOpsDemoMsUpgradeItemRequest, Make);
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem::GetServiceName() const
{
	return TEXT("LiveOpsDemoMs");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem::GetEndpointName() const
{
	return TEXT("UpgradeItem");
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem::GetApiClass() const
{
	return UBeamLiveOpsDemoMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem::GetRequestClass() const
{
	return ULiveOpsDemoMsUpgradeItemRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem::GetResponseClass() const
{
	return ULiveOpsDemoMsUpgradeItemResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem::GetRequestSuccessDelegateName() const
{
	return TEXT("OnLiveOpsDemoMsUpgradeItemSuccess");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem::GetRequestErrorDelegateName() const
{
	return TEXT("OnLiveOpsDemoMsUpgradeItemError");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMsUpgradeItem::GetRequestCompleteDelegateName() const
{
	return TEXT("OnLiveOpsDemoMsUpgradeItemComplete");
}

#undef LOCTEXT_NAMESPACE
