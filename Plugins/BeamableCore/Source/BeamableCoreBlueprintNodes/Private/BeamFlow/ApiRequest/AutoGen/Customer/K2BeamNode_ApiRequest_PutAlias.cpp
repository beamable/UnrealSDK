

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PutAlias.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PutAliasRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutAlias"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutAlias::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutAlias::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PutAlias);
}

FName UK2BeamNode_ApiRequest_PutAlias::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutAliasRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutAlias::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PutAlias::GetEndpointName() const
{
	return TEXT("PutAlias");
}

UClass* UK2BeamNode_ApiRequest_PutAlias::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAlias::GetRequestClass() const
{
	return UPutAliasRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAlias::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutAlias::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutAliasSuccess");
}

FString UK2BeamNode_ApiRequest_PutAlias::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutAliasError");
}

FString UK2BeamNode_ApiRequest_PutAlias::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutAliasComplete");
}

#undef LOCTEXT_NAMESPACE
