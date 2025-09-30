

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PutCustomer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PutCustomerRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutCustomer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutCustomer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutCustomer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PutCustomer);
}

FName UK2BeamNode_ApiRequest_PutCustomer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutCustomerRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutCustomer::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PutCustomer::GetEndpointName() const
{
	return TEXT("PutCustomer");
}

UClass* UK2BeamNode_ApiRequest_PutCustomer::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutCustomer::GetRequestClass() const
{
	return UPutCustomerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutCustomer::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutCustomer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutCustomerSuccess");
}

FString UK2BeamNode_ApiRequest_PutCustomer::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutCustomerError");
}

FString UK2BeamNode_ApiRequest_PutCustomer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutCustomerComplete");
}

#undef LOCTEXT_NAMESPACE
