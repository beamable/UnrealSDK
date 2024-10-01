

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/LiveOpsDemoMS/K2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamLiveOpsDemoMSApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/LiveOpsDemoMS/LiveOpsDemoMSUpgradeItemRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSUpgradeItemResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMSApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLiveOpsDemoMSApi, UpgradeItem);
}

FName UK2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(ULiveOpsDemoMSUpgradeItemRequest, Make);
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem::GetServiceName() const
{
	return TEXT("LiveOpsDemoMS");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem::GetEndpointName() const
{
	return TEXT("UpgradeItem");
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem::GetApiClass() const
{
	return UBeamLiveOpsDemoMSApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem::GetRequestClass() const
{
	return ULiveOpsDemoMSUpgradeItemRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem::GetResponseClass() const
{
	return ULiveOpsDemoMSUpgradeItemResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem::GetRequestSuccessDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSUpgradeItemSuccess");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem::GetRequestErrorDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSUpgradeItemError");
}

FString UK2BeamNode_ApiRequest_LiveOpsDemoMSUpgradeItem::GetRequestCompleteDelegateName() const
{
	return TEXT("OnLiveOpsDemoMSUpgradeItemComplete");
}

#undef LOCTEXT_NAMESPACE
