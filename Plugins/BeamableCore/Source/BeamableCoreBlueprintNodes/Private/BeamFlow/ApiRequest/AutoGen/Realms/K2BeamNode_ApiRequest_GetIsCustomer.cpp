

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetIsCustomer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetIsCustomerRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetIsCustomer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetIsCustomer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetIsCustomer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetIsCustomer);
}

FName UK2BeamNode_ApiRequest_GetIsCustomer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetIsCustomerRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetIsCustomer::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetIsCustomer::GetEndpointName() const
{
	return TEXT("GetIsCustomer");
}

UClass* UK2BeamNode_ApiRequest_GetIsCustomer::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetIsCustomer::GetRequestClass() const
{
	return UGetIsCustomerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetIsCustomer::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetIsCustomer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetIsCustomerSuccess");
}

FString UK2BeamNode_ApiRequest_GetIsCustomer::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetIsCustomerError");
}

FString UK2BeamNode_ApiRequest_GetIsCustomer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetIsCustomerComplete");
}

#undef LOCTEXT_NAMESPACE
