

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Inventory/K2BeamNode_ApiRequest_PutInventory.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/PutInventoryRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutInventory"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutInventory::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutInventory::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, PutInventory);
}

FName UK2BeamNode_ApiRequest_PutInventory::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutInventoryRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutInventory::GetServiceName() const
{
	return TEXT("Inventory");
}

FString UK2BeamNode_ApiRequest_PutInventory::GetEndpointName() const
{
	return TEXT("PutInventory");
}

UClass* UK2BeamNode_ApiRequest_PutInventory::GetApiClass() const
{
	return UBeamInventoryApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutInventory::GetRequestClass() const
{
	return UPutInventoryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutInventory::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutInventory::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutInventorySuccess");
}

FString UK2BeamNode_ApiRequest_PutInventory::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutInventoryError");
}

FString UK2BeamNode_ApiRequest_PutInventory::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutInventoryComplete");
}

#undef LOCTEXT_NAMESPACE
