

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/PlayerTicket/K2BeamNode_ApiRequest_GetMatchmakingTickets.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerTicketApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/PlayerTicket/GetMatchmakingTicketsRequest.h"
#include "BeamableCore/Public/AutoGen/TicketQueryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetMatchmakingTickets"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetMatchmakingTickets::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerTicketApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetMatchmakingTickets::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerTicketApi, GetMatchmakingTickets);
}

FName UK2BeamNode_ApiRequest_GetMatchmakingTickets::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetMatchmakingTicketsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetMatchmakingTickets::GetServiceName() const
{
	return TEXT("PlayerTicket");
}

FString UK2BeamNode_ApiRequest_GetMatchmakingTickets::GetEndpointName() const
{
	return TEXT("GetMatchmakingTickets");
}

UClass* UK2BeamNode_ApiRequest_GetMatchmakingTickets::GetApiClass() const
{
	return UBeamPlayerTicketApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMatchmakingTickets::GetRequestClass() const
{
	return UGetMatchmakingTicketsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMatchmakingTickets::GetResponseClass() const
{
	return UTicketQueryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetMatchmakingTickets::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetMatchmakingTicketsSuccess");
}

FString UK2BeamNode_ApiRequest_GetMatchmakingTickets::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetMatchmakingTicketsError");
}

FString UK2BeamNode_ApiRequest_GetMatchmakingTickets::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetMatchmakingTicketsComplete");
}

#undef LOCTEXT_NAMESPACE
