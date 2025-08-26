

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PostVerify.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PostVerifyRequest.h"
#include "BeamableCore/Public/AutoGen/CustomerActorNewCustomerResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostVerify"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostVerify::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostVerify::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PostVerify);
}

FName UK2BeamNode_ApiRequest_PostVerify::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostVerifyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostVerify::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PostVerify::GetEndpointName() const
{
	return TEXT("PostVerify");
}

UClass* UK2BeamNode_ApiRequest_PostVerify::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostVerify::GetRequestClass() const
{
	return UPostVerifyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostVerify::GetResponseClass() const
{
	return UCustomerActorNewCustomerResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostVerify::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostVerifySuccess");
}

FString UK2BeamNode_ApiRequest_PostVerify::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostVerifyError");
}

FString UK2BeamNode_ApiRequest_PostVerify::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostVerifyComplete");
}

#undef LOCTEXT_NAMESPACE
