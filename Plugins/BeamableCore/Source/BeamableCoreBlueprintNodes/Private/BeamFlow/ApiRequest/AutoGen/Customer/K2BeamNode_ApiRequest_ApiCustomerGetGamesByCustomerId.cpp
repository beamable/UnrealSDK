

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/ApiCustomerGetGamesByCustomerIdRequest.h"
#include "BeamableCore/Public/AutoGen/GetGamesResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, ApiCustomerGetGamesByCustomerId);
}

FName UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiCustomerGetGamesByCustomerIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId::GetEndpointName() const
{
	return TEXT("ApiCustomerGetGamesByCustomerId");
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId::GetRequestClass() const
{
	return UApiCustomerGetGamesByCustomerIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId::GetResponseClass() const
{
	return UGetGamesResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiCustomerGetGamesByCustomerIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiCustomerGetGamesByCustomerIdError");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiCustomerGetGamesByCustomerIdComplete");
}

#undef LOCTEXT_NAMESPACE
