

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Inventory/K2BeamNode_ApiRequest_DeleteTransaction.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/DeleteTransactionRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteTransaction"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteTransaction::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteTransaction::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, DeleteTransaction);
}

FName UK2BeamNode_ApiRequest_DeleteTransaction::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteTransactionRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteTransaction::GetServiceName() const
{
	return TEXT("Inventory");
}

FString UK2BeamNode_ApiRequest_DeleteTransaction::GetEndpointName() const
{
	return TEXT("DeleteTransaction");
}

UClass* UK2BeamNode_ApiRequest_DeleteTransaction::GetApiClass() const
{
	return UBeamInventoryApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteTransaction::GetRequestClass() const
{
	return UDeleteTransactionRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteTransaction::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteTransaction::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteTransactionSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteTransaction::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteTransactionError");
}

FString UK2BeamNode_ApiRequest_DeleteTransaction::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteTransactionComplete");
}

#undef LOCTEXT_NAMESPACE
