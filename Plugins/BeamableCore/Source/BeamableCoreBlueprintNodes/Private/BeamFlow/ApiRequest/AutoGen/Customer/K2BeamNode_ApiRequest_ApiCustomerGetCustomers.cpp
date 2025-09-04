

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_ApiCustomerGetCustomers.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/ApiCustomerGetCustomersRequest.h"
#include "BeamableCore/Public/AutoGen/CustomerActorCustomersResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiCustomerGetCustomers"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiCustomerGetCustomers::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiCustomerGetCustomers::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetCustomers);
}

FName UK2BeamNode_ApiRequest_ApiCustomerGetCustomers::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiCustomerGetCustomersRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetCustomers::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetCustomers::GetEndpointName() const
{
	return TEXT("GetCustomers");
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetCustomers::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetCustomers::GetRequestClass() const
{
	return UApiCustomerGetCustomersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetCustomers::GetResponseClass() const
{
	return UCustomerActorCustomersResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetCustomers::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiCustomerGetCustomersSuccess");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetCustomers::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiCustomerGetCustomersError");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetCustomers::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiCustomerGetCustomersComplete");
}

#undef LOCTEXT_NAMESPACE
