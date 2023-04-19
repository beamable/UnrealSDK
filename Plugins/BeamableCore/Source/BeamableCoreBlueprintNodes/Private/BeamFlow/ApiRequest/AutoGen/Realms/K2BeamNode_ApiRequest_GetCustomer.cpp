

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetCustomer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetCustomerRequest.h"
#include "BeamableCore/Public/AutoGen/CustomerViewResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCustomer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCustomer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCustomer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetCustomer);
}

FName UK2BeamNode_ApiRequest_GetCustomer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCustomerRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCustomer::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetCustomer::GetEndpointName() const
{
	return TEXT("GetCustomer");
}

UClass* UK2BeamNode_ApiRequest_GetCustomer::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCustomer::GetRequestClass() const
{
	return UGetCustomerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCustomer::GetResponseClass() const
{
	return UCustomerViewResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCustomer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCustomerSuccess");
}

FString UK2BeamNode_ApiRequest_GetCustomer::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCustomerError");
}

FString UK2BeamNode_ApiRequest_GetCustomer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCustomerComplete");
}

#undef LOCTEXT_NAMESPACE
