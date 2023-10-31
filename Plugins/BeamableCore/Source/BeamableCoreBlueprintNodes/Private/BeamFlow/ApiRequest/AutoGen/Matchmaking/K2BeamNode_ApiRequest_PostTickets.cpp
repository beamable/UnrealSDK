

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Matchmaking/K2BeamNode_ApiRequest_PostTickets.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/PostTicketsRequest.h"
#include "BeamableCore/Public/AutoGen/TicketReservationResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTickets"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTickets::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTickets::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, PostTickets);
}

FName UK2BeamNode_ApiRequest_PostTickets::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTicketsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTickets::GetServiceName() const
{
	return TEXT("Matchmaking");
}

FString UK2BeamNode_ApiRequest_PostTickets::GetEndpointName() const
{
	return TEXT("PostTickets");
}

UClass* UK2BeamNode_ApiRequest_PostTickets::GetApiClass() const
{
	return UBeamMatchmakingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTickets::GetRequestClass() const
{
	return UPostTicketsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTickets::GetResponseClass() const
{
	return UTicketReservationResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTickets::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTicketsSuccess");
}

FString UK2BeamNode_ApiRequest_PostTickets::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTicketsError");
}

FString UK2BeamNode_ApiRequest_PostTickets::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTicketsComplete");
}

#undef LOCTEXT_NAMESPACE
