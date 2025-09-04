

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/ApiCustomerGetGamesByCustomerIdAndGameIdRequest.h"
#include "BeamableCore/Public/AutoGen/GetGamesResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, ApiCustomerGetGamesByCustomerIdAndGameId);
}

FName UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiCustomerGetGamesByCustomerIdAndGameIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId::GetEndpointName() const
{
	return TEXT("ApiCustomerGetGamesByCustomerIdAndGameId");
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId::GetRequestClass() const
{
	return UApiCustomerGetGamesByCustomerIdAndGameIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId::GetResponseClass() const
{
	return UGetGamesResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiCustomerGetGamesByCustomerIdAndGameIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiCustomerGetGamesByCustomerIdAndGameIdError");
}

FString UK2BeamNode_ApiRequest_ApiCustomerGetGamesByCustomerIdAndGameId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiCustomerGetGamesByCustomerIdAndGameIdComplete");
}

#undef LOCTEXT_NAMESPACE
