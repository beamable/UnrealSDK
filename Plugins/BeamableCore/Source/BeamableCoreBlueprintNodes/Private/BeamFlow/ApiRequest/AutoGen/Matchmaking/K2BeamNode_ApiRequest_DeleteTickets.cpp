

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Matchmaking/K2BeamNode_ApiRequest_DeleteTickets.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/DeleteTicketsRequest.h"
#include "BeamableCore/Public/AutoGen/ApiMatchmakingTicketsDeleteTicketResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteTickets"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteTickets::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteTickets::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, DeleteTickets);
}

FName UK2BeamNode_ApiRequest_DeleteTickets::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteTicketsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteTickets::GetServiceName() const
{
	return TEXT("Matchmaking");
}

FString UK2BeamNode_ApiRequest_DeleteTickets::GetEndpointName() const
{
	return TEXT("DeleteTickets");
}

UClass* UK2BeamNode_ApiRequest_DeleteTickets::GetApiClass() const
{
	return UBeamMatchmakingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteTickets::GetRequestClass() const
{
	return UDeleteTicketsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteTickets::GetResponseClass() const
{
	return UApiMatchmakingTicketsDeleteTicketResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteTickets::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteTicketsSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteTickets::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteTicketsError");
}

FString UK2BeamNode_ApiRequest_DeleteTickets::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteTicketsComplete");
}

#undef LOCTEXT_NAMESPACE
