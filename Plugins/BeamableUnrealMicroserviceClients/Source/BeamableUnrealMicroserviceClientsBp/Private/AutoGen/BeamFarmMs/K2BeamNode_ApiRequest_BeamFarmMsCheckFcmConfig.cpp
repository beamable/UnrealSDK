

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsCheckFcmConfigRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/FcmConfigStatus.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, CheckFcmConfig);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsCheckFcmConfigRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig::GetEndpointName() const
{
	return TEXT("CheckFcmConfig");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig::GetRequestClass() const
{
	return UBeamFarmMsCheckFcmConfigRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig::GetResponseClass() const
{
	return UFcmConfigStatus::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsCheckFcmConfigSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsCheckFcmConfigError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsCheckFcmConfig::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsCheckFcmConfigComplete");
}

#undef LOCTEXT_NAMESPACE
