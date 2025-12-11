

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payment/K2BeamNode_ApiRequest_PostReceipt.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payment/PostReceiptRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostReceipt"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostReceipt::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostReceipt::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentApi, PostReceipt);
}

FName UK2BeamNode_ApiRequest_PostReceipt::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostReceiptRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostReceipt::GetServiceName() const
{
	return TEXT("Payment");
}

FString UK2BeamNode_ApiRequest_PostReceipt::GetEndpointName() const
{
	return TEXT("PostReceipt");
}

UClass* UK2BeamNode_ApiRequest_PostReceipt::GetApiClass() const
{
	return UBeamPaymentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostReceipt::GetRequestClass() const
{
	return UPostReceiptRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostReceipt::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostReceipt::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostReceiptSuccess");
}

FString UK2BeamNode_ApiRequest_PostReceipt::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostReceiptError");
}

FString UK2BeamNode_ApiRequest_PostReceipt::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostReceiptComplete");
}

#undef LOCTEXT_NAMESPACE
