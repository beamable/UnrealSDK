

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Matchmaking/K2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/ApiMatchmakingGetTicketsByIdRequest.h"
#include "BeamableCore/Public/AutoGen/Ticket.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, ApiMatchmakingGetTicketsById);
}

FName UK2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiMatchmakingGetTicketsByIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById::GetServiceName() const
{
	return TEXT("Matchmaking");
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById::GetEndpointName() const
{
	return TEXT("ApiMatchmakingGetTicketsById");
}

UClass* UK2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById::GetApiClass() const
{
	return UBeamMatchmakingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById::GetRequestClass() const
{
	return UApiMatchmakingGetTicketsByIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById::GetResponseClass() const
{
	return UTicket::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiMatchmakingGetTicketsByIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiMatchmakingGetTicketsByIdError");
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetTicketsById::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiMatchmakingGetTicketsByIdComplete");
}

#undef LOCTEXT_NAMESPACE
