

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Presence/K2BeamNode_ApiRequest_PostQuery.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPresenceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Presence/PostQueryRequest.h"
#include "BeamableCore/Public/AutoGen/PlayersStatusResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostQuery"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostQuery::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPresenceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostQuery::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPresenceApi, PostQuery);
}

FName UK2BeamNode_ApiRequest_PostQuery::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostQueryRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostQuery::GetServiceName() const
{
	return TEXT("Presence");
}

FString UK2BeamNode_ApiRequest_PostQuery::GetEndpointName() const
{
	return TEXT("PostQuery");
}

UClass* UK2BeamNode_ApiRequest_PostQuery::GetApiClass() const
{
	return UBeamPresenceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostQuery::GetRequestClass() const
{
	return UPostQueryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostQuery::GetResponseClass() const
{
	return UPlayersStatusResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostQuery::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostQuerySuccess");
}

FString UK2BeamNode_ApiRequest_PostQuery::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostQueryError");
}

FString UK2BeamNode_ApiRequest_PostQuery::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostQueryComplete");
}

#undef LOCTEXT_NAMESPACE
