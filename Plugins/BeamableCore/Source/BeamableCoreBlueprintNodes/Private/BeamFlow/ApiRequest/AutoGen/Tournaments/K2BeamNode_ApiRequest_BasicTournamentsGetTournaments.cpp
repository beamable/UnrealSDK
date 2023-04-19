

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_BasicTournamentsGetTournaments.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/BasicTournamentsGetTournamentsRequest.h"
#include "BeamableCore/Public/AutoGen/TournamentQueryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicTournamentsGetTournaments"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicTournamentsGetTournaments::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicTournamentsGetTournaments::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, BasicTournamentsGetTournaments);
}

FName UK2BeamNode_ApiRequest_BasicTournamentsGetTournaments::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicTournamentsGetTournamentsRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetTournaments::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetTournaments::GetEndpointName() const
{
	return TEXT("BasicTournamentsGetTournaments");
}

UClass* UK2BeamNode_ApiRequest_BasicTournamentsGetTournaments::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicTournamentsGetTournaments::GetRequestClass() const
{
	return UBasicTournamentsGetTournamentsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicTournamentsGetTournaments::GetResponseClass() const
{
	return UTournamentQueryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetTournaments::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicTournamentsGetTournamentsSuccess");
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetTournaments::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicTournamentsGetTournamentsError");
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetTournaments::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicTournamentsGetTournamentsComplete");
}

#undef LOCTEXT_NAMESPACE
