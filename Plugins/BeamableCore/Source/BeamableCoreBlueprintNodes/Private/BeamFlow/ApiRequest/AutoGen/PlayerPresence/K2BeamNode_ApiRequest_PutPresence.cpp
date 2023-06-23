

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/PlayerPresence/K2BeamNode_ApiRequest_PutPresence.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerPresenceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/PlayerPresence/PutPresenceRequest.h"
#include "BeamableCore/Public/AutoGen/ApiPlayersPresencePutPlayerPresenceResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutPresence"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutPresence::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerPresenceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutPresence::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerPresenceApi, PutPresence);
}

FName UK2BeamNode_ApiRequest_PutPresence::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutPresenceRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutPresence::GetServiceName() const
{
	return TEXT("PlayerPresence");
}

FString UK2BeamNode_ApiRequest_PutPresence::GetEndpointName() const
{
	return TEXT("PutPresence");
}

UClass* UK2BeamNode_ApiRequest_PutPresence::GetApiClass() const
{
	return UBeamPlayerPresenceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPresence::GetRequestClass() const
{
	return UPutPresenceRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPresence::GetResponseClass() const
{
	return UApiPlayersPresencePutPlayerPresenceResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutPresence::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutPresenceSuccess");
}

FString UK2BeamNode_ApiRequest_PutPresence::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutPresenceError");
}

FString UK2BeamNode_ApiRequest_PutPresence::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutPresenceComplete");
}

#undef LOCTEXT_NAMESPACE
