

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Inventory/K2BeamNode_ApiRequest_PutTransfer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/PutTransferRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutTransfer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutTransfer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutTransfer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, PutTransfer);
}

FName UK2BeamNode_ApiRequest_PutTransfer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutTransferRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutTransfer::GetServiceName() const
{
	return TEXT("Inventory");
}

FString UK2BeamNode_ApiRequest_PutTransfer::GetEndpointName() const
{
	return TEXT("PutTransfer");
}

UClass* UK2BeamNode_ApiRequest_PutTransfer::GetApiClass() const
{
	return UBeamInventoryApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutTransfer::GetRequestClass() const
{
	return UPutTransferRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutTransfer::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutTransfer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutTransferSuccess");
}

FString UK2BeamNode_ApiRequest_PutTransfer::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutTransferError");
}

FString UK2BeamNode_ApiRequest_PutTransfer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutTransferComplete");
}

#undef LOCTEXT_NAMESPACE
