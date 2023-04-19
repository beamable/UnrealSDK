

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_GetStandingsGroup.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/GetStandingsGroupRequest.h"
#include "BeamableCore/Public/AutoGen/GetStandingsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetStandingsGroup"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetStandingsGroup::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetStandingsGroup::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetStandingsGroup);
}

FName UK2BeamNode_ApiRequest_GetStandingsGroup::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetStandingsGroupRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetStandingsGroup::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_GetStandingsGroup::GetEndpointName() const
{
	return TEXT("GetStandingsGroup");
}

UClass* UK2BeamNode_ApiRequest_GetStandingsGroup::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetStandingsGroup::GetRequestClass() const
{
	return UGetStandingsGroupRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetStandingsGroup::GetResponseClass() const
{
	return UGetStandingsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetStandingsGroup::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetStandingsGroupSuccess");
}

FString UK2BeamNode_ApiRequest_GetStandingsGroup::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetStandingsGroupError");
}

FString UK2BeamNode_ApiRequest_GetStandingsGroup::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetStandingsGroupComplete");
}

#undef LOCTEXT_NAMESPACE
