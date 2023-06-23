

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/PlayerPresence/K2BeamNode_ApiRequest_PutPresenceStatus.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerPresenceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/PlayerPresence/PutPresenceStatusRequest.h"
#include "BeamableCore/Public/AutoGen/OnlineStatus.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutPresenceStatus"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutPresenceStatus::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerPresenceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutPresenceStatus::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerPresenceApi, PutPresenceStatus);
}

FName UK2BeamNode_ApiRequest_PutPresenceStatus::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutPresenceStatusRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutPresenceStatus::GetServiceName() const
{
	return TEXT("PlayerPresence");
}

FString UK2BeamNode_ApiRequest_PutPresenceStatus::GetEndpointName() const
{
	return TEXT("PutPresenceStatus");
}

UClass* UK2BeamNode_ApiRequest_PutPresenceStatus::GetApiClass() const
{
	return UBeamPlayerPresenceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPresenceStatus::GetRequestClass() const
{
	return UPutPresenceStatusRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPresenceStatus::GetResponseClass() const
{
	return UOnlineStatus::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutPresenceStatus::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutPresenceStatusSuccess");
}

FString UK2BeamNode_ApiRequest_PutPresenceStatus::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutPresenceStatusError");
}

FString UK2BeamNode_ApiRequest_PutPresenceStatus::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutPresenceStatusComplete");
}

#undef LOCTEXT_NAMESPACE
