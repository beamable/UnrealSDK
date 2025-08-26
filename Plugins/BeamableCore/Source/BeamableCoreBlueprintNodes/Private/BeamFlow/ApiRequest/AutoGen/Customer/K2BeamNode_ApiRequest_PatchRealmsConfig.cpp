

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PatchRealmsConfig.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PatchRealmsConfigRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PatchRealmsConfig"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PatchRealmsConfig::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PatchRealmsConfig::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PatchRealmsConfig);
}

FName UK2BeamNode_ApiRequest_PatchRealmsConfig::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPatchRealmsConfigRequest, Make);
}

FString UK2BeamNode_ApiRequest_PatchRealmsConfig::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PatchRealmsConfig::GetEndpointName() const
{
	return TEXT("PatchRealmsConfig");
}

UClass* UK2BeamNode_ApiRequest_PatchRealmsConfig::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PatchRealmsConfig::GetRequestClass() const
{
	return UPatchRealmsConfigRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PatchRealmsConfig::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PatchRealmsConfig::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPatchRealmsConfigSuccess");
}

FString UK2BeamNode_ApiRequest_PatchRealmsConfig::GetRequestErrorDelegateName() const
{
	return TEXT("OnPatchRealmsConfigError");
}

FString UK2BeamNode_ApiRequest_PatchRealmsConfig::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPatchRealmsConfigComplete");
}

#undef LOCTEXT_NAMESPACE
