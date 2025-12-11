

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/ObjectPaymentsGetPaymentsByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetPayments);
}

FName UK2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectPaymentsGetPaymentsByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId::GetEndpointName() const
{
	return TEXT("GetPayments");
}

UClass* UK2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId::GetRequestClass() const
{
	return UObjectPaymentsGetPaymentsByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectPaymentsGetPaymentsByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectPaymentsGetPaymentsByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectPaymentsGetPaymentsByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectPaymentsGetPaymentsByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
