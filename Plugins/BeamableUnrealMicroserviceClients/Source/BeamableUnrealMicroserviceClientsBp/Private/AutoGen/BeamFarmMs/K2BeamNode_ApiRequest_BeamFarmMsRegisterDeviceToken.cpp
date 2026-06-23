

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsRegisterDeviceTokenRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, RegisterDeviceToken);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsRegisterDeviceTokenRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken::GetEndpointName() const
{
	return TEXT("RegisterDeviceToken");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken::GetRequestClass() const
{
	return UBeamFarmMsRegisterDeviceTokenRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken::GetResponseClass() const
{
	return URegisterResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsRegisterDeviceTokenSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsRegisterDeviceTokenError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsRegisterDeviceToken::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsRegisterDeviceTokenComplete");
}

#undef LOCTEXT_NAMESPACE
