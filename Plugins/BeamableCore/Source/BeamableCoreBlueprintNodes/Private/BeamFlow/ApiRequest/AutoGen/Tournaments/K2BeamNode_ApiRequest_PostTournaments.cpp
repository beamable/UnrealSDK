

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_PostTournaments.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/PostTournamentsRequest.h"
#include "BeamableCore/Public/AutoGen/PlayerStatus.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTournaments"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTournaments::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTournaments::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, PostTournaments);
}

FName UK2BeamNode_ApiRequest_PostTournaments::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTournamentsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTournaments::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_PostTournaments::GetEndpointName() const
{
	return TEXT("PostTournaments");
}

UClass* UK2BeamNode_ApiRequest_PostTournaments::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTournaments::GetRequestClass() const
{
	return UPostTournamentsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTournaments::GetResponseClass() const
{
	return UPlayerStatus::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTournaments::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTournamentsSuccess");
}

FString UK2BeamNode_ApiRequest_PostTournaments::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTournamentsError");
}

FString UK2BeamNode_ApiRequest_PostTournaments::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTournamentsComplete");
}

#undef LOCTEXT_NAMESPACE
