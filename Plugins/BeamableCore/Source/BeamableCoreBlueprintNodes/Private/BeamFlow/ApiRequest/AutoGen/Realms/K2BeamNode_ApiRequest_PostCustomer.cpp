

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PostCustomer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostCustomerRequest.h"
#include "BeamableCore/Public/AutoGen/NewCustomerResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostCustomer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostCustomer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostCustomer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PostCustomer);
}

FName UK2BeamNode_ApiRequest_PostCustomer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostCustomerRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostCustomer::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PostCustomer::GetEndpointName() const
{
	return TEXT("PostCustomer");
}

UClass* UK2BeamNode_ApiRequest_PostCustomer::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCustomer::GetRequestClass() const
{
	return UPostCustomerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCustomer::GetResponseClass() const
{
	return UNewCustomerResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostCustomer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostCustomerSuccess");
}

FString UK2BeamNode_ApiRequest_PostCustomer::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostCustomerError");
}

FString UK2BeamNode_ApiRequest_PostCustomer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostCustomerComplete");
}

#undef LOCTEXT_NAMESPACE
