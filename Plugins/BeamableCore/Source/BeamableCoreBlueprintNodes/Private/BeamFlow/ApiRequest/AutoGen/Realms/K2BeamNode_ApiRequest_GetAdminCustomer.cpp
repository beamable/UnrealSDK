

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetAdminCustomer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetAdminCustomerRequest.h"
#include "BeamableCore/Public/AutoGen/CustomerResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAdminCustomer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAdminCustomer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAdminCustomer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetAdminCustomer);
}

FName UK2BeamNode_ApiRequest_GetAdminCustomer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAdminCustomerRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAdminCustomer::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetAdminCustomer::GetEndpointName() const
{
	return TEXT("GetAdminCustomer");
}

UClass* UK2BeamNode_ApiRequest_GetAdminCustomer::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAdminCustomer::GetRequestClass() const
{
	return UGetAdminCustomerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAdminCustomer::GetResponseClass() const
{
	return UCustomerResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAdminCustomer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAdminCustomerSuccess");
}

FString UK2BeamNode_ApiRequest_GetAdminCustomer::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAdminCustomerError");
}

FString UK2BeamNode_ApiRequest_GetAdminCustomer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAdminCustomerComplete");
}

#undef LOCTEXT_NAMESPACE
