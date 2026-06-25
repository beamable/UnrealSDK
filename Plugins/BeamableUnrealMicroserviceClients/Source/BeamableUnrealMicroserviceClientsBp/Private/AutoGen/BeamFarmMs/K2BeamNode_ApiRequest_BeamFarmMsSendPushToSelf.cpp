

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsSendPushToSelfRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, SendPushToSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsSendPushToSelfRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf::GetEndpointName() const
{
	return TEXT("SendPushToSelf");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf::GetRequestClass() const
{
	return UBeamFarmMsSendPushToSelfRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf::GetResponseClass() const
{
	return USendResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsSendPushToSelfSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsSendPushToSelfError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsSendPushToSelf::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsSendPushToSelfComplete");
}

#undef LOCTEXT_NAMESPACE
