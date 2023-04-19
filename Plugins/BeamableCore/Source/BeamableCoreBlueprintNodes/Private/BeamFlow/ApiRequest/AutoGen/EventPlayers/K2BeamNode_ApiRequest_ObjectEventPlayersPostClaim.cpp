

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/EventPlayers/K2BeamNode_ApiRequest_ObjectEventPlayersPostClaim.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventPlayersApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/EventPlayers/ObjectEventPlayersPostClaimRequest.h"
#include "BeamableCore/Public/AutoGen/EventClaimResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectEventPlayersPostClaim"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaim::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventPlayersApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaim::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventPlayersApi, PostClaim);
}

FName UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaim::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectEventPlayersPostClaimRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaim::GetServiceName() const
{
	return TEXT("EventPlayers");
}

FString UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaim::GetEndpointName() const
{
	return TEXT("PostClaim");
}

UClass* UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaim::GetApiClass() const
{
	return UBeamEventPlayersApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaim::GetRequestClass() const
{
	return UObjectEventPlayersPostClaimRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaim::GetResponseClass() const
{
	return UEventClaimResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaim::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectEventPlayersPostClaimSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaim::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectEventPlayersPostClaimError");
}

FString UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaim::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectEventPlayersPostClaimComplete");
}

#undef LOCTEXT_NAMESPACE
