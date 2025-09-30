

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PostCustomers.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PostCustomersRequest.h"
#include "BeamableCore/Public/AutoGen/CustomerActorNewCustomerResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostCustomers"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostCustomers::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostCustomers::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PostCustomers);
}

FName UK2BeamNode_ApiRequest_PostCustomers::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostCustomersRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostCustomers::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PostCustomers::GetEndpointName() const
{
	return TEXT("PostCustomers");
}

UClass* UK2BeamNode_ApiRequest_PostCustomers::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCustomers::GetRequestClass() const
{
	return UPostCustomersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCustomers::GetResponseClass() const
{
	return UCustomerActorNewCustomerResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostCustomers::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostCustomersSuccess");
}

FString UK2BeamNode_ApiRequest_PostCustomers::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostCustomersError");
}

FString UK2BeamNode_ApiRequest_PostCustomers::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostCustomersComplete");
}

#undef LOCTEXT_NAMESPACE
