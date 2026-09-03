

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsListRegisteredPlayersRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisteredPlayerList.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, ListRegisteredPlayers);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsListRegisteredPlayersRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers::GetEndpointName() const
{
	return TEXT("ListRegisteredPlayers");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers::GetRequestClass() const
{
	return UBeamFarmMsListRegisteredPlayersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers::GetResponseClass() const
{
	return URegisteredPlayerList::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsListRegisteredPlayersSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsListRegisteredPlayersError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsListRegisteredPlayers::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsListRegisteredPlayersComplete");
}

#undef LOCTEXT_NAMESPACE
