

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PostConfig.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostConfigRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostConfig"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostConfig::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostConfig::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PostConfig);
}

FName UK2BeamNode_ApiRequest_PostConfig::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostConfigRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostConfig::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PostConfig::GetEndpointName() const
{
	return TEXT("PostConfig");
}

UClass* UK2BeamNode_ApiRequest_PostConfig::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostConfig::GetRequestClass() const
{
	return UPostConfigRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostConfig::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostConfig::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostConfigSuccess");
}

FString UK2BeamNode_ApiRequest_PostConfig::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostConfigError");
}

FString UK2BeamNode_ApiRequest_PostConfig::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostConfigComplete");
}

#undef LOCTEXT_NAMESPACE
