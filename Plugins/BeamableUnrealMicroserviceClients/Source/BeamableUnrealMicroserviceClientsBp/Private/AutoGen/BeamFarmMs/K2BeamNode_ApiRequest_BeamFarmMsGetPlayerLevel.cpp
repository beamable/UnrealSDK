

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsGetPlayerLevelRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetPlayerLevelResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetPlayerLevel);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsGetPlayerLevelRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel::GetEndpointName() const
{
	return TEXT("GetPlayerLevel");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel::GetRequestClass() const
{
	return UBeamFarmMsGetPlayerLevelRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel::GetResponseClass() const
{
	return UGetPlayerLevelResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsGetPlayerLevelSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsGetPlayerLevelError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetPlayerLevel::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsGetPlayerLevelComplete");
}

#undef LOCTEXT_NAMESPACE
