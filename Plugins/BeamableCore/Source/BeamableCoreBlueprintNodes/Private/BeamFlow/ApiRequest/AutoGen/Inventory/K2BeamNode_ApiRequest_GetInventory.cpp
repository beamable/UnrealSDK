

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Inventory/K2BeamNode_ApiRequest_GetInventory.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/GetInventoryRequest.h"
#include "BeamableCore/Public/AutoGen/InventoryView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetInventory"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetInventory::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetInventory::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetInventory);
}

FName UK2BeamNode_ApiRequest_GetInventory::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetInventoryRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetInventory::GetServiceName() const
{
	return TEXT("Inventory");
}

FString UK2BeamNode_ApiRequest_GetInventory::GetEndpointName() const
{
	return TEXT("GetInventory");
}

UClass* UK2BeamNode_ApiRequest_GetInventory::GetApiClass() const
{
	return UBeamInventoryApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetInventory::GetRequestClass() const
{
	return UGetInventoryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetInventory::GetResponseClass() const
{
	return UInventoryView::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetInventory::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetInventorySuccess");
}

FString UK2BeamNode_ApiRequest_GetInventory::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetInventoryError");
}

FString UK2BeamNode_ApiRequest_GetInventory::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetInventoryComplete");
}

#undef LOCTEXT_NAMESPACE
