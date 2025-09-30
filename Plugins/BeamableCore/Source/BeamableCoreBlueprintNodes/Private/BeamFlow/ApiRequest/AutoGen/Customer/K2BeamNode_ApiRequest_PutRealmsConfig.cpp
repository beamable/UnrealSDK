

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PutRealmsConfig.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PutRealmsConfigRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutRealmsConfig"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutRealmsConfig::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutRealmsConfig::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PutRealmsConfig);
}

FName UK2BeamNode_ApiRequest_PutRealmsConfig::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutRealmsConfigRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutRealmsConfig::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PutRealmsConfig::GetEndpointName() const
{
	return TEXT("PutRealmsConfig");
}

UClass* UK2BeamNode_ApiRequest_PutRealmsConfig::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutRealmsConfig::GetRequestClass() const
{
	return UPutRealmsConfigRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutRealmsConfig::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutRealmsConfig::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutRealmsConfigSuccess");
}

FString UK2BeamNode_ApiRequest_PutRealmsConfig::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutRealmsConfigError");
}

FString UK2BeamNode_ApiRequest_PutRealmsConfig::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutRealmsConfigComplete");
}

#undef LOCTEXT_NAMESPACE
