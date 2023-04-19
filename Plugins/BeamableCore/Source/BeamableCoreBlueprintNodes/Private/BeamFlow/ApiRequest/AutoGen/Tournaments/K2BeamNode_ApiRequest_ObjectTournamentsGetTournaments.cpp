

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_ObjectTournamentsGetTournaments.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/ObjectTournamentsGetTournamentsRequest.h"
#include "BeamableCore/Public/AutoGen/TournamentClientView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectTournamentsGetTournaments"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectTournamentsGetTournaments::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectTournamentsGetTournaments::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, ObjectTournamentsGetTournaments);
}

FName UK2BeamNode_ApiRequest_ObjectTournamentsGetTournaments::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectTournamentsGetTournamentsRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectTournamentsGetTournaments::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_ObjectTournamentsGetTournaments::GetEndpointName() const
{
	return TEXT("ObjectTournamentsGetTournaments");
}

UClass* UK2BeamNode_ApiRequest_ObjectTournamentsGetTournaments::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectTournamentsGetTournaments::GetRequestClass() const
{
	return UObjectTournamentsGetTournamentsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectTournamentsGetTournaments::GetResponseClass() const
{
	return UTournamentClientView::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectTournamentsGetTournaments::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectTournamentsGetTournamentsSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectTournamentsGetTournaments::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectTournamentsGetTournamentsError");
}

FString UK2BeamNode_ApiRequest_ObjectTournamentsGetTournaments::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectTournamentsGetTournamentsComplete");
}

#undef LOCTEXT_NAMESPACE
