

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PostCustomerVerify.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostCustomerVerifyRequest.h"
#include "BeamableCore/Public/AutoGen/NewCustomerResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostCustomerVerify"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostCustomerVerify::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostCustomerVerify::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PostCustomerVerify);
}

FName UK2BeamNode_ApiRequest_PostCustomerVerify::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostCustomerVerifyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostCustomerVerify::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PostCustomerVerify::GetEndpointName() const
{
	return TEXT("PostCustomerVerify");
}

UClass* UK2BeamNode_ApiRequest_PostCustomerVerify::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCustomerVerify::GetRequestClass() const
{
	return UPostCustomerVerifyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCustomerVerify::GetResponseClass() const
{
	return UNewCustomerResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostCustomerVerify::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostCustomerVerifySuccess");
}

FString UK2BeamNode_ApiRequest_PostCustomerVerify::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostCustomerVerifyError");
}

FString UK2BeamNode_ApiRequest_PostCustomerVerify::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostCustomerVerifyComplete");
}

#undef LOCTEXT_NAMESPACE
