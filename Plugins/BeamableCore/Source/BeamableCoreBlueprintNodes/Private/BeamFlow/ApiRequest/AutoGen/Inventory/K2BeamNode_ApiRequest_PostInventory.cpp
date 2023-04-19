

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Inventory/K2BeamNode_ApiRequest_PostInventory.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/PostInventoryRequest.h"
#include "BeamableCore/Public/AutoGen/InventoryView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostInventory"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostInventory::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostInventory::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, PostInventory);
}

FName UK2BeamNode_ApiRequest_PostInventory::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostInventoryRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostInventory::GetServiceName() const
{
	return TEXT("Inventory");
}

FString UK2BeamNode_ApiRequest_PostInventory::GetEndpointName() const
{
	return TEXT("PostInventory");
}

UClass* UK2BeamNode_ApiRequest_PostInventory::GetApiClass() const
{
	return UBeamInventoryApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostInventory::GetRequestClass() const
{
	return UPostInventoryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostInventory::GetResponseClass() const
{
	return UInventoryView::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostInventory::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostInventorySuccess");
}

FString UK2BeamNode_ApiRequest_PostInventory::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostInventoryError");
}

FString UK2BeamNode_ApiRequest_PostInventory::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostInventoryComplete");
}

#undef LOCTEXT_NAMESPACE
