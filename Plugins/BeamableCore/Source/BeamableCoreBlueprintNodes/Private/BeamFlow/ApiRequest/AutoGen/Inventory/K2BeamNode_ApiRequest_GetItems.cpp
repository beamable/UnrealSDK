

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Inventory/K2BeamNode_ApiRequest_GetItems.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/GetItemsRequest.h"
#include "BeamableCore/Public/AutoGen/ItemContentResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetItems"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetItems::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetItems::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetItems);
}

FName UK2BeamNode_ApiRequest_GetItems::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetItemsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetItems::GetServiceName() const
{
	return TEXT("Inventory");
}

FString UK2BeamNode_ApiRequest_GetItems::GetEndpointName() const
{
	return TEXT("GetItems");
}

UClass* UK2BeamNode_ApiRequest_GetItems::GetApiClass() const
{
	return UBeamInventoryApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetItems::GetRequestClass() const
{
	return UGetItemsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetItems::GetResponseClass() const
{
	return UItemContentResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetItems::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetItemsSuccess");
}

FString UK2BeamNode_ApiRequest_GetItems::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetItemsError");
}

FString UK2BeamNode_ApiRequest_GetItems::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetItemsComplete");
}

#undef LOCTEXT_NAMESPACE
