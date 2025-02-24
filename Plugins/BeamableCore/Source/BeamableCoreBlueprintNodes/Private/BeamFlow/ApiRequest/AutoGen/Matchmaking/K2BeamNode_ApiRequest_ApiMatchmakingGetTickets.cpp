

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Matchmaking/K2BeamNode_ApiRequest_ApiMatchmakingGetTickets.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Matchmaking/ApiMatchmakingGetTicketsRequest.h"
#include "BeamableCore/Public/AutoGen/TicketQueryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiMatchmakingGetTickets"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiMatchmakingGetTickets::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiMatchmakingGetTickets::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, ApiMatchmakingGetTickets);
}

FName UK2BeamNode_ApiRequest_ApiMatchmakingGetTickets::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiMatchmakingGetTicketsRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetTickets::GetServiceName() const
{
	return TEXT("Matchmaking");
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetTickets::GetEndpointName() const
{
	return TEXT("ApiMatchmakingGetTickets");
}

UClass* UK2BeamNode_ApiRequest_ApiMatchmakingGetTickets::GetApiClass() const
{
	return UBeamMatchmakingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiMatchmakingGetTickets::GetRequestClass() const
{
	return UApiMatchmakingGetTicketsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiMatchmakingGetTickets::GetResponseClass() const
{
	return UTicketQueryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetTickets::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiMatchmakingGetTicketsSuccess");
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetTickets::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiMatchmakingGetTicketsError");
}

FString UK2BeamNode_ApiRequest_ApiMatchmakingGetTickets::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiMatchmakingGetTicketsComplete");
}

#undef LOCTEXT_NAMESPACE
