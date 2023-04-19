

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_GetStandings.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/GetStandingsRequest.h"
#include "BeamableCore/Public/AutoGen/GetStandingsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetStandings"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetStandings::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetStandings::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetStandings);
}

FName UK2BeamNode_ApiRequest_GetStandings::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetStandingsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetStandings::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_GetStandings::GetEndpointName() const
{
	return TEXT("GetStandings");
}

UClass* UK2BeamNode_ApiRequest_GetStandings::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetStandings::GetRequestClass() const
{
	return UGetStandingsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetStandings::GetResponseClass() const
{
	return UGetStandingsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetStandings::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetStandingsSuccess");
}

FString UK2BeamNode_ApiRequest_GetStandings::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetStandingsError");
}

FString UK2BeamNode_ApiRequest_GetStandings::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetStandingsComplete");
}

#undef LOCTEXT_NAMESPACE
