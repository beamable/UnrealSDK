

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/ApiCustomerGetConfigByCustomerIdRequest.h"
#include "BeamableCore/Public/AutoGen/RealmConfigResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetConfig);
}

FName UK2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiCustomerGetConfigByCustomerIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId::GetEndpointName() const
{
	return TEXT("GetConfig");
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId::GetRequestClass() const
{
	return UApiCustomerGetConfigByCustomerIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId::GetResponseClass() const
{
	return URealmConfigResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiCustomerGetConfigByCustomerIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiCustomerGetConfigByCustomerIdError");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetConfigByCustomerId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiCustomerGetConfigByCustomerIdComplete");
}

#undef LOCTEXT_NAMESPACE
