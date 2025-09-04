

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_BasicRealmsGetCustomer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/BasicRealmsGetCustomerRequest.h"
#include "BeamableCore/Public/AutoGen/CustomerViewResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicRealmsGetCustomer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicRealmsGetCustomer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicRealmsGetCustomer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetCustomer);
}

FName UK2BeamNode_ApiRequest_BasicRealmsGetCustomer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicRealmsGetCustomerRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetCustomer::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetCustomer::GetEndpointName() const
{
	return TEXT("GetCustomer");
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsGetCustomer::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsGetCustomer::GetRequestClass() const
{
	return UBasicRealmsGetCustomerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsGetCustomer::GetResponseClass() const
{
	return UCustomerViewResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetCustomer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicRealmsGetCustomerSuccess");
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetCustomer::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicRealmsGetCustomerError");
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetCustomer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicRealmsGetCustomerComplete");
}

#undef LOCTEXT_NAMESPACE
