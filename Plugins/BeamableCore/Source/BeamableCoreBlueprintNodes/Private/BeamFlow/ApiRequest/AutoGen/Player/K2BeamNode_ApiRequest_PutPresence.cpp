

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Player/K2BeamNode_ApiRequest_PutPresence.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Player/PutPresenceRequest.h"
#include "BeamableCore/Public/AutoGen/ApiPlayersPresencePutPlayerPresenceResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutPresence"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutPresence::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutPresence::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerApi, PutPresence);
}

FName UK2BeamNode_ApiRequest_PutPresence::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutPresenceRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutPresence::GetServiceName() const
{
	return TEXT("Player");
}

FString UK2BeamNode_ApiRequest_PutPresence::GetEndpointName() const
{
	return TEXT("PutPresence");
}

UClass* UK2BeamNode_ApiRequest_PutPresence::GetApiClass() const
{
	return UBeamPlayerApi::StaticClass();
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
