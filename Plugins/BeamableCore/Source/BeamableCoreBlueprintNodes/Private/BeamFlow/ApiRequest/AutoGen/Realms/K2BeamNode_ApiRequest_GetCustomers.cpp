

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetCustomers.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetCustomersRequest.h"
#include "BeamableCore/Public/AutoGen/CustomersResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCustomers"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCustomers::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCustomers::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetCustomers);
}

FName UK2BeamNode_ApiRequest_GetCustomers::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCustomersRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCustomers::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetCustomers::GetEndpointName() const
{
	return TEXT("GetCustomers");
}

UClass* UK2BeamNode_ApiRequest_GetCustomers::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCustomers::GetRequestClass() const
{
	return UGetCustomersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCustomers::GetResponseClass() const
{
	return UCustomersResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCustomers::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCustomersSuccess");
}

FString UK2BeamNode_ApiRequest_GetCustomers::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCustomersError");
}

FString UK2BeamNode_ApiRequest_GetCustomers::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCustomersComplete");
}

#undef LOCTEXT_NAMESPACE
