

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetCustomerAliasAvailable.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetCustomerAliasAvailableRequest.h"
#include "BeamableCore/Public/AutoGen/AliasAvailableResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCustomerAliasAvailable"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCustomerAliasAvailable::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCustomerAliasAvailable::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetCustomerAliasAvailable);
}

FName UK2BeamNode_ApiRequest_GetCustomerAliasAvailable::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCustomerAliasAvailableRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCustomerAliasAvailable::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetCustomerAliasAvailable::GetEndpointName() const
{
	return TEXT("GetCustomerAliasAvailable");
}

UClass* UK2BeamNode_ApiRequest_GetCustomerAliasAvailable::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCustomerAliasAvailable::GetRequestClass() const
{
	return UGetCustomerAliasAvailableRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCustomerAliasAvailable::GetResponseClass() const
{
	return UAliasAvailableResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCustomerAliasAvailable::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCustomerAliasAvailableSuccess");
}

FString UK2BeamNode_ApiRequest_GetCustomerAliasAvailable::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCustomerAliasAvailableError");
}

FString UK2BeamNode_ApiRequest_GetCustomerAliasAvailable::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCustomerAliasAvailableComplete");
}

#undef LOCTEXT_NAMESPACE
