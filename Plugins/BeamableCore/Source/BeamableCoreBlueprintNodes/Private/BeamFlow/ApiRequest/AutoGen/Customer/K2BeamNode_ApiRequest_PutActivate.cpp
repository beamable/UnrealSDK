

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PutActivate.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PutActivateRequest.h"
#include "BeamableCore/Public/AutoGen/ApiCustomersActivatePutCustomerResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutActivate"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutActivate::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutActivate::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PutActivate);
}

FName UK2BeamNode_ApiRequest_PutActivate::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutActivateRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutActivate::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PutActivate::GetEndpointName() const
{
	return TEXT("PutActivate");
}

UClass* UK2BeamNode_ApiRequest_PutActivate::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutActivate::GetRequestClass() const
{
	return UPutActivateRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutActivate::GetResponseClass() const
{
	return UApiCustomersActivatePutCustomerResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutActivate::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutActivateSuccess");
}

FString UK2BeamNode_ApiRequest_PutActivate::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutActivateError");
}

FString UK2BeamNode_ApiRequest_PutActivate::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutActivateComplete");
}

#undef LOCTEXT_NAMESPACE
