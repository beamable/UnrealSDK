

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/ObjectTournamentsGetTournamentsByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/TournamentClientView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, ObjectTournamentsGetTournamentsByObjectId);
}

FName UK2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectTournamentsGetTournamentsByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId::GetEndpointName() const
{
	return TEXT("ObjectTournamentsGetTournamentsByObjectId");
}

UClass* UK2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId::GetRequestClass() const
{
	return UObjectTournamentsGetTournamentsByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId::GetResponseClass() const
{
	return UTournamentClientView::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectTournamentsGetTournamentsByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectTournamentsGetTournamentsByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectTournamentsGetTournamentsByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectTournamentsGetTournamentsByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
