

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/EventPlayers/K2BeamNode_ApiRequest_GetEventPlayers.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventPlayersApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/EventPlayers/GetEventPlayersRequest.h"
#include "BeamableCore/Public/AutoGen/EventPlayerView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetEventPlayers"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetEventPlayers::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventPlayersApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetEventPlayers::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventPlayersApi, GetEventPlayers);
}

FName UK2BeamNode_ApiRequest_GetEventPlayers::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetEventPlayersRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetEventPlayers::GetServiceName() const
{
	return TEXT("EventPlayers");
}

FString UK2BeamNode_ApiRequest_GetEventPlayers::GetEndpointName() const
{
	return TEXT("GetEventPlayers");
}

UClass* UK2BeamNode_ApiRequest_GetEventPlayers::GetApiClass() const
{
	return UBeamEventPlayersApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetEventPlayers::GetRequestClass() const
{
	return UGetEventPlayersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetEventPlayers::GetResponseClass() const
{
	return UEventPlayerView::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetEventPlayers::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetEventPlayersSuccess");
}

FString UK2BeamNode_ApiRequest_GetEventPlayers::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetEventPlayersError");
}

FString UK2BeamNode_ApiRequest_GetEventPlayers::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetEventPlayersComplete");
}

#undef LOCTEXT_NAMESPACE
