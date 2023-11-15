

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Matchmaking/K2BeamNode_ApiRequest_GetTickets.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/GetTicketsRequest.h"
#include "BeamableCore/Public/AutoGen/Ticket.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetTickets"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetTickets::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetTickets::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetTickets);
}

FName UK2BeamNode_ApiRequest_GetTickets::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetTicketsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetTickets::GetServiceName() const
{
	return TEXT("Matchmaking");
}

FString UK2BeamNode_ApiRequest_GetTickets::GetEndpointName() const
{
	return TEXT("GetTickets");
}

UClass* UK2BeamNode_ApiRequest_GetTickets::GetApiClass() const
{
	return UBeamMatchmakingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetTickets::GetRequestClass() const
{
	return UGetTicketsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetTickets::GetResponseClass() const
{
	return UTicket::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetTickets::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetTicketsSuccess");
}

FString UK2BeamNode_ApiRequest_GetTickets::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetTicketsError");
}

FString UK2BeamNode_ApiRequest_GetTickets::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetTicketsComplete");
}

#undef LOCTEXT_NAMESPACE
