

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PutConfig.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PutConfigRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutConfig"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutConfig::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutConfig::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PutConfig);
}

FName UK2BeamNode_ApiRequest_PutConfig::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutConfigRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutConfig::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PutConfig::GetEndpointName() const
{
	return TEXT("PutConfig");
}

UClass* UK2BeamNode_ApiRequest_PutConfig::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutConfig::GetRequestClass() const
{
	return UPutConfigRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutConfig::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutConfig::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutConfigSuccess");
}

FString UK2BeamNode_ApiRequest_PutConfig::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutConfigError");
}

FString UK2BeamNode_ApiRequest_PutConfig::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutConfigComplete");
}

#undef LOCTEXT_NAMESPACE
