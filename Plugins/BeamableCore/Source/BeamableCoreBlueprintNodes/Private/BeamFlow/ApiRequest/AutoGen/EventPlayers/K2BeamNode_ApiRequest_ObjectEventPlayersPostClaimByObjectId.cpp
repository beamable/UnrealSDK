

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/EventPlayers/K2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventPlayersApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/EventPlayers/ObjectEventPlayersPostClaimByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/EventClaimResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventPlayersApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventPlayersApi, PostClaim);
}

FName UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectEventPlayersPostClaimByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId::GetServiceName() const
{
	return TEXT("EventPlayers");
}

FString UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId::GetEndpointName() const
{
	return TEXT("PostClaim");
}

UClass* UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId::GetApiClass() const
{
	return UBeamEventPlayersApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId::GetRequestClass() const
{
	return UObjectEventPlayersPostClaimByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId::GetResponseClass() const
{
	return UEventClaimResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectEventPlayersPostClaimByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectEventPlayersPostClaimByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectEventPlayersPostClaimByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectEventPlayersPostClaimByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
