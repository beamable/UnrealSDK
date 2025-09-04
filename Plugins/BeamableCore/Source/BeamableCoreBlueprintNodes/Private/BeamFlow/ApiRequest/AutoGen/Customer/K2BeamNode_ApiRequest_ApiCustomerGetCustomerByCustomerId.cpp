

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/ApiCustomerGetCustomerByCustomerIdRequest.h"
#include "BeamableCore/Public/AutoGen/CustomerActorCustomerView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetCustomer);
}

FName UK2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiCustomerGetCustomerByCustomerIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId::GetEndpointName() const
{
	return TEXT("GetCustomer");
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId::GetRequestClass() const
{
	return UApiCustomerGetCustomerByCustomerIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId::GetResponseClass() const
{
	return UCustomerActorCustomerView::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiCustomerGetCustomerByCustomerIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiCustomerGetCustomerByCustomerIdError");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetCustomerByCustomerId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiCustomerGetCustomerByCustomerIdComplete");
}

#undef LOCTEXT_NAMESPACE
