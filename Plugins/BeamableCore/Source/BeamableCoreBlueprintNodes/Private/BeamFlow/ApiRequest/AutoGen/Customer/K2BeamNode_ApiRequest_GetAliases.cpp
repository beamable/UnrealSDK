

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_GetAliases.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/GetAliasesRequest.h"
#include "BeamableCore/Public/AutoGen/CustomerActorAliasAvailableResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAliases"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAliases::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAliases::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetAliases);
}

FName UK2BeamNode_ApiRequest_GetAliases::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAliasesRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAliases::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_GetAliases::GetEndpointName() const
{
	return TEXT("GetAliases");
}

UClass* UK2BeamNode_ApiRequest_GetAliases::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAliases::GetRequestClass() const
{
	return UGetAliasesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAliases::GetResponseClass() const
{
	return UCustomerActorAliasAvailableResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAliases::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAliasesSuccess");
}

FString UK2BeamNode_ApiRequest_GetAliases::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAliasesError");
}

FString UK2BeamNode_ApiRequest_GetAliases::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAliasesComplete");
}

#undef LOCTEXT_NAMESPACE
