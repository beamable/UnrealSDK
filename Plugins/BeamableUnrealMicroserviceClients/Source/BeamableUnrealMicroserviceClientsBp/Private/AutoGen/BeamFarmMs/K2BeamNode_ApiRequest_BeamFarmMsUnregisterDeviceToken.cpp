

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsUnregisterDeviceTokenRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/UnregisterResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, UnregisterDeviceToken);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsUnregisterDeviceTokenRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken::GetEndpointName() const
{
	return TEXT("UnregisterDeviceToken");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken::GetRequestClass() const
{
	return UBeamFarmMsUnregisterDeviceTokenRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken::GetResponseClass() const
{
	return UUnregisterResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsUnregisterDeviceTokenSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsUnregisterDeviceTokenError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsUnregisterDeviceToken::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsUnregisterDeviceTokenComplete");
}

#undef LOCTEXT_NAMESPACE
